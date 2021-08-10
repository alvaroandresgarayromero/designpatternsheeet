variable "a_aws_user" {
    type = map
    sensitive = true
    default = {
        "access_key" = ""
        "secret_key" = ""
        "token" = ""
    }
}

variable "a_region" {
    type = string
    description = "The AWS region to use."
    default = "us-east-1"
}