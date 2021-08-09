# TODO: Define the output variable for the lambda function.
output "lambda_arn"{
    description = "ARN of Lambda Function"
    value = "${aws_lambda_function.tf_lambda.arn}"
}