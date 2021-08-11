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
  access_key = var.a_aws_user["access_key"]
  secret_key = var.a_aws_user["secret_key"]
  token = var.a_aws_user["token"]
  profile = "default"
  region  = var.a_region
}

# Use Terraform to create S3 Bucket
resource "aws_s3_bucket" "tf_bucket" {
  bucket = "tf-bucket-encryption"
}