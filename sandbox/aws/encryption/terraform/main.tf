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
  access_key = var.a_aws_user[0].access_key
  secret_key = var.a_aws_user[0].secret_key
  token = var.a_aws_user[0].token
  profile = "default"
  region  = var.a_region
}

# Using Terraform IAM policy to create policy with SQS and CloudWatch permissions
# This policy is identical to: AWSLambdaSQSQueueExecutionRole
resource "aws_iam_policy" "tf_lambda_policy" {
  name        = "tf_lambda_policy"
  path        = "/"
  description = "IAM policy for lambda to accept SQS events, and logging from a lambda"

  policy = jsonencode({ 
    "Version": "2012-10-17",
    "Statement": [
        {
            "Effect": "Allow",
            "Action": [
                "sqs:ReceiveMessage",
                "sqs:DeleteMessage",
                "sqs:GetQueueAttributes",
                "logs:CreateLogGroup",
                "logs:CreateLogStream",
                "logs:PutLogEvents"
            ],
            "Resource": "*"
        }
    ]
})
}

# Using Terraform Data Source to create "Assume Role Policy"
data "aws_iam_policy_document" "tf_lambda_asume_role" {
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
# - This role utilizes the tf_lambda_assume_role to allow Lambda to assume this role
resource "aws_iam_role" "tf_lambda_role" {
  name                = "tf_lambda_role"
  assume_role_policy  = data.aws_iam_policy_document.tf_lambda_asume_role.json
  managed_policy_arns = [aws_iam_policy.tf_lambda_policy.arn]
}

# Using Terraform to zip python file
data "archive_file" "lambda_archive" {
  type        = "zip"
  source_file = "greet_lambda.py"
  output_path = "lambda_function.zip"
}


# Using Terraform to create Lambda service
resource "aws_lambda_function" "tf_lambda" {
  filename      = "lambda_function.zip" 
  package_type  = "Zip" 
  function_name = "tf_lambda_function"
  role          = aws_iam_role.tf_lambda_role.arn
  runtime       = "python3.8"
  handler       = "greet_lambda.lambda_handler"

  environment {
    variables = {
        greeting = "Hello"
    }
  }
}

# Use Terraform to create SQS Service
resource "aws_sqs_queue" "tf_queue" {
  name                        = "tf_queue"
  fifo_queue                  = false
}

# User Terraform to add SQS as trigger for Lambda function
resource "aws_lambda_event_source_mapping" "trigger_event" {
  event_source_arn = aws_sqs_queue.tf_queue.arn
  function_name    = aws_lambda_function.tf_lambda.arn
}

# Success! Now from SQS console trigger event and 
# verify lambda is triggered through cloudwatch