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

This project utilizes Terraform for provisioning an S3 bucket with server-side encryption enabled.
The C++ application then uses the AWS C++ SDK to write a text file into the S3 bucket.

Getting Started
----------------

1. Set the AWS credentials
    Verify that your user AWS credentials are configured inside the active docker container

        - Use environment variables provided under the 'aws' directory to source into docker
        - Or run '$ aws configure' on the CLI. Follow the prompt.

2. Deploy an S3 bucket with all its configurations into AWS with Terraform
    Go to the terraform directory, and deploy the resources.

    .. code-block:: bash

        root@5976e1426a62:/app/sandbox/aws/encryption# cd terraform
        root@5976e1426a62:/app/sandbox/aws/encryption/terraform#

    Initialize terraform

    .. code-block:: bash

        root@5976e1426a62:../encryption/terraform# terraform init

    Apply terraform (create resources in AWS). Once completed,
    go to the AWS Console to verify that terraform create the desired resources
    with the expected configurations

    .. code-block:: bash

        root@5976e1426a62:.../encryption/terraform# terraform apply

    Destroy terraform (to remove AWS resources)

    .. code-block:: bash

        root@5976e1426a62:.../encryption/terraform# terraform destroy

3. Create a C++ executable that writes into the S3 Bucket
    Go to the app directory and compile the C++ application in a build directory

    .. code-block:: bash

        root@5976e1426a62:.../encryption/app# mkdir out
        root@5976e1426a62:.../encryption/app/out# cd out
        root@5976e1426a62:.../encryption/app/out# cmake ..
        root@5976e1426a62:.../encryption/app/out# make

    Run and verify the application writes into the S3 bucket by going to into the AWS console

    .. code-block:: bash

        root@5976e1426a62:.../encryption/app/out# ./encryption