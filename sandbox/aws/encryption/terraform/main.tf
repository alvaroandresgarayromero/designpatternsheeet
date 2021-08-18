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
  region  = var.a_region
  profile = "default"

}

# Use Terraform to create S3 Bucket
resource "aws_s3_bucket" "tf_bucket" {
  bucket = "tf-bucket-encryption"
}