output "lambda_arn"{
    description = "ARN of Lambda Function"
    value = "${aws_lambda_function.tf_lambda.arn}"
}

output "lambda_role_uniqueid"{
    description = "ARN of Lambda Function role id"
    value = "${aws_iam_role.tf_lambda_role.unique_id}"
}

output "account_id" {
    value = "${data.aws_caller_identity.current.account_id}"
}

output "caller_arn" {
    value = "${data.aws_caller_identity.current.arn}"
}

output "caller_user" {
    value = "${data.aws_caller_identity.current.user_id}"
}