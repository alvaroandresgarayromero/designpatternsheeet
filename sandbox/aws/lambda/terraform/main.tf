terraform {
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 3.27"
    }
  }

  required_version = ">= 0.14.9"
}

provider "aws" {
  profile = "default"
  region  = var.a_region
}

# Get access to AWS Account ID, User ID, and ARN
data "aws_caller_identity" "current" {}

# Use Terraform to create S3 Bucket for lambda to write to
resource "aws_s3_bucket" "tf_bucket" {
  bucket = "tf-bucket"

  server_side_encryption_configuration {
    rule {
      apply_server_side_encryption_by_default {
        sse_algorithm = "AES256"
      }
    }
  }
}

# block all public access into this S3 bucket
resource "aws_s3_bucket_public_access_block" "tf_bucket" {
  bucket = aws_s3_bucket.tf_bucket.id

  block_public_acls   = true
  block_public_policy = true
  ignore_public_acls = true
  restrict_public_buckets = true
}

# Use Terraform to create SQS Service
# SQS Event failures related to the queue go to the dead letter queue
resource "aws_sqs_queue" "tf_dead_letter_queue" {
  name                       = "tf_dead_letter_queue"
  delay_seconds              = 0
  max_message_size           = 262144 # 256 KB
  message_retention_seconds  = 86400  #  1 day
  receive_wait_time_seconds  = 0      # seconds
  visibility_timeout_seconds = 30     # seconds

  fifo_queue                  = false
}

# Apply principle of least privilege on the SQS
# owner allows permission for lambda and SDK.
resource "aws_sqs_queue_policy" "tf_dead_letter_queue_access_policy" {
  queue_url = aws_sqs_queue.tf_dead_letter_queue.id

  policy = jsonencode({
    "Version": "2012-10-17",
    "Id": "sqspolicy",
    "Statement": [
      {
        Sid: "_owner_statement",
        Effect: "Allow",
        Principal: {
          "AWS": "arn:aws:iam::${data.aws_caller_identity.current.account_id}:root"
        },
        Action: "SQS:*",
        Resource: "${aws_sqs_queue.tf_dead_letter_queue.arn}"
      }
    ]
  })
}

# Use Terraform to create SQS Service
# SQS Messages go to this queue
resource "aws_sqs_queue" "tf_queue" {
  name                       = "tf_queue"
  delay_seconds              = 0
  max_message_size           = 262144 # 256 KB
  message_retention_seconds  = 86400  #  1 day
  receive_wait_time_seconds  = 20     # seconds
  visibility_timeout_seconds = 30     # seconds
  redrive_policy = jsonencode({
    deadLetterTargetArn = aws_sqs_queue.tf_dead_letter_queue.arn
    maxReceiveCount     = 2
  })
  fifo_queue                  = false
}

# Apply principle of least privilege on the SQS
# owner allows permission for lambda and SDK.
resource "aws_sqs_queue_policy" "tf_queue_access_policy" {
  queue_url = aws_sqs_queue.tf_queue.id

  policy = jsonencode({
    "Version": "2012-10-17",
    "Id": "sqspolicy",
    "Statement": [
      {
        Sid: "_owner_statement",
        Effect: "Allow",
        Principal: {
          "AWS": "arn:aws:iam::${data.aws_caller_identity.current.account_id}:root"
        },
        Action: "SQS:*",
        Resource: "${aws_sqs_queue.tf_queue.arn}"
      }
    ]
  })
}

# Using Terraform IAM policy to create policy
# This policy handles permissions that will part of an aws lambda role.
# AWS lambda will then assume role and have access to write to S3, SQS, and CloudWatch.
resource "aws_iam_policy" "tf_lambda_policy" {
  name        = "tf_lambda_policy"
  path        = "/"
  description = "IAM policy for lambda to accept SQS events, and logging from a lambda"

  policy = jsonencode({ 
    "Version": "2012-10-17",
    "Statement": [
        {
           Effect: "Allow",
           Action: [
              "s3:PutObject",
              "sqs:SendMessage"
           ],
           Resource: [
              "${aws_s3_bucket.tf_bucket.arn}/*",
              "${aws_sqs_queue.tf_queue.arn}"
           ]
        },
        {
            Effect: "Allow",
            Action: [
                "logs:CreateLogGroup",
                "logs:CreateLogStream",
                "logs:PutLogEvents"
            ],
            Resource: "*"
        }
    ]
})
}

# Using Terraform Data Source to create Trust Relationship: "Assume Role Policy"
# Allow lambda to be the only one that can assume the role.
data "aws_iam_policy_document" "tf_lambda_assume_role" {
  statement {
    actions = ["sts:AssumeRole"]

    principals {
      type        = "Service"
      identifiers = ["lambda.amazonaws.com"]
    }
  }
}

# Using Terraform to create Role for lambda service to use
# - This role utilizes the tf_lambda_policy for permissions
# - This role utilizes the tf_lambda_assume_role to enable Lambda to assume this role
resource "aws_iam_role" "tf_lambda_role" {
  name                = "tf_lambda_role"
  assume_role_policy  = data.aws_iam_policy_document.tf_lambda_assume_role.json
  managed_policy_arns = [aws_iam_policy.tf_lambda_policy.arn]
}

# Using Terraform to create Lambda service
resource "aws_lambda_function" "tf_lambda" {
  filename      = "lambda.zip"
  package_type  = "Zip" 
  function_name = "tf_lambda_function"
  role          = aws_iam_role.tf_lambda_role.arn
  runtime       = "provided"
  handler       = "lambda"

  environment {
    variables = {
        greeting = "Hello"
    }
  }
}

resource "aws_lambda_function_event_invoke_config" "tf_lambda_destinations" {
  function_name = aws_lambda_function.tf_lambda.function_name

  destination_config {
    on_failure {
      destination = aws_sqs_queue.tf_queue.arn
    }

    on_success {
      destination = aws_sqs_queue.tf_queue.arn
    }
  }
}

# Apply principle of least privilege on the S3 Bucket
# The policy below deny's all writes except if its from the expected
# lambda role unique id, which is a string type.
# aws iam get-role --role-name <role-name>
# This means any lambda that assume the tf_lambda_role will have access
# to write.
resource "aws_s3_bucket_policy" "tf_bucket" {
  bucket = aws_s3_bucket.tf_bucket.id

  policy = jsonencode({
    "Version": "2012-10-17",
    "Statement": [
      {
        Effect: "Deny",
        Principal: "*",
        Action: "s3:PutObject",
        Resource: "${aws_s3_bucket.tf_bucket.arn}/*"
        Condition: {
          StringNotLike: {
            "aws:userId": "${aws_iam_role.tf_lambda_role.unique_id}:*"
          }
        }
      }
    ]
  })
}

# Create SNS service
# SNS will be used to trigger lambda processing
resource "aws_sns_topic" "tf_topic" {
  name = "tf_topic"
  fifo_topic = "false"

}

# sns subscription: aws lambda subscription to sqs
resource "aws_sns_topic_subscription" "tf_topic_target" {
  topic_arn = aws_sns_topic.tf_topic.arn
  protocol  = "lambda"
  endpoint  = aws_lambda_function.tf_lambda.arn
}

# lambda resource-based policy: allow sns to invoke lambda function
resource "aws_lambda_permission" "with_sns" {
  statement_id  = "AllowExecutionFromSNS"
  action        = "lambda:InvokeFunction"
  function_name = aws_lambda_function.tf_lambda.function_name
  principal     = "sns.amazonaws.com"
  source_arn    = aws_sns_topic.tf_topic.arn
}
