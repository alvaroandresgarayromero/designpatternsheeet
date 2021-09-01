# TODO: Define the output variable for the lambda function.
output "lambda_arn"{
    description = "ARN of Lambda Function"
    value = "${aws_lambda_function.tf_lambda.arn}"
}

output "lambda_role_uniqueid"{
    description = "ARN of Lambda Function role id"
    value = "${aws_iam_role.tf_lambda_role.unique_id}"
}

