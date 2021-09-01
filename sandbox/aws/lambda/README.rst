.. meta::
    :description lang=en: AWS C++
    :keywords: C++, AWS

==========
Overview
==========

.. contents:: Table of Contents
    :backlinks: none

Description
-------------

In this project, we utilize aws lambda runtime library to create a C++ lambda function, and
Terraform to deploy lambda, S3, and SQS resources into AWS. Then we use the AWS C++ SDK to create a C++ app
to perform logical operations on AWS SQS to trigger the C++ lambda function as well as send some payload data.
The lambda function process will create an object inside the S3 bucket with the payload data in a human readable json string.
Finally, the app will retrieve, and download the object file from S3 bucket into our local host.

The signal path in summary is as follow:

   C++ app communicates with SQS (triggers lambda and send payload) --->
   C++ lambda function (writes payload into an object in S3 bucket) --->
   C++ app downloads the object with the payload from S3 bucket to host

Getting Started
-----------------

1. Set the AWS credentials
    Verify that your user AWS credentials are configured inside the active docker container

        - Use environment variables provided under the 'aws' directory to source into docker
        - Or run '$ aws configure' on the CLI. Follow the prompt.

2. Create C++ package lambda executable with all its dependencies
    Go to the lambda_function directory, and compile the C++ application in a build directory

    .. code-block:: bash

        root@5976e1426a62:/app/sandbox/aws/lambda/lambda_function# mkdir out
        root@5976e1426a62:/app/sandbox/aws/lambda/lambda_function# cd out
        root@5976e1426a62:/app/sandbox/aws/lambda/lambda_function/out# cmake ..
        root@5976e1426a62:/app/sandbox/aws/lambda/lambda_function/out# make

    Package the executable with all its dependencies using the AWS lambda package tool.
    A lambda.zip file will created.

    .. code-block:: bash

        root@5976e1426a62:/app/sandbox/aws/lambda/lambda_function/out# make aws-lambda-package-lambda

3. Deploy lambda, S3, and SQS with all its configurations into AWS using Terraform
    Go to the lambda_function build directory, and move the 'lambda.zip' file into the terraform folder

    .. code-block:: bash

        root@5976e1426a62:/app/sandbox/aws/lambda/lambda_function/out# mv lambda.zip ../../terraform

    Go to the terraform directory, and deploy the resources.
    In the AWS console, verify that the expected lambda and SQS resources have been created, SQS
    is linked as a trigger, and that the expected role has been created.

    .. code-block:: bash

        root@5976e1426a62:/app/sandbox/aws/lambda/terraform# terraform init
        root@5976e1426a62:/app/sandbox/aws/lambda/terraform# terraform apply

    Verify aws lambda is functional by triggering lambda with the AWS CLI.
    The payload value will be written into lambda_output.txt

    .. code-block:: bash

        echo '{"name": "Alvaro", "message": "This was processed by AWS Lambda" }' > clean_payload.txt

    .. code-block:: bash

        openssl base64 -out encoded_payload.txt -in clean_payload.txt

    .. code-block:: bash

        aws lambda invoke --function-name tf_lambda_function \
                   --payload file://encoded_payload.txt \
                   lambda_output.txt

    Verify aws lambda is functional by triggering lambda with the AWS CLI.
    The payload value will be written into an object in S3 bucket.

    .. code-block:: bash

        aws s3 cp s3://tf-bucket/payload.txt .