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

# Using Terraform IAM policy to create policy with SQS and CloudWatch permissions
# This policy is identical to: AWSLambdaSQSQueueExecutionRole
# Plus enable lambda only write access into our S3 bucket
resource "aws_iam_policy" "tf_lambda_policy" {
  name        = "tf_lambda_policy"
  path        = "/"
  description = "IAM policy for lambda to accept SQS events, and logging from a lambda"

  policy = jsonencode({ 
    "Version": "2012-10-17",
    "Statement": [
        {
           Effect: "Allow",
           Action: "s3:PutObject",
           Resource: "${aws_s3_bucket.tf_bucket.arn}/*"
        },
        {
            Effect: "Allow",
            Action: [
                "sqs:ReceiveMessage",
                "sqs:DeleteMessage",
                "sqs:GetQueueAttributes",
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

# Let's apply principle of least privilege on the S3 Bucket
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

# Use Terraform to create SQS Service
resource "aws_sqs_queue" "tf_queue" {
  name                        = "tf_queue"
  fifo_queue                  = false
}

# Use Terraform to add SQS as trigger for Lambda function
resource "aws_lambda_event_source_mapping" "trigger_event" {
  event_source_arn = aws_sqs_queue.tf_queue.arn
  function_name    = aws_lambda_function.tf_lambda.arn
}


# Success! Now from SQS console trigger event and 
# verify lambda is triggered through cloudwatch