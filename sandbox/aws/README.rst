.. meta::
    :description lang=en: AWS C++
    :keywords: C++, AWS

==========
Overview
==========

.. contents:: Table of Contents
    :backlinks: none

Getting Started
-----------------

This project utilizes Terraform for provisioning, and maintaining AWS Infrastructures, and
AWS C++ SDK for performing operations on the cloud resources.
The reason behind using Terraform for provisioning cloud resources is to
create a habit of using a SaaS that is cloud agnostic. Therefore,
each AWS project sub-directory will have their own terraform, and app folder.

1. To begin, the AWS credentials need to be configure inside the docker container
    There are two methods currently supported.

    Using shared credentials/configuration file

    Using environment variables to override shared credentials/configuration file.
        - Open the aws.env file located in this root folder, and update the environment variables contents with the AWS user keys.
        - Stop the active container, if it is running. Docker needs to consume the updated ENV file.

            .. code-block:: bash

                # docker-compose has already been configure to look for the aws.env file.
                # So we simply need to run it.
                $ sudo docker-compose up


        - Verify the environment variables have been set inside the docker container

            .. code-block:: bash

                root@5976e1426a62:/app# echo $AWS_ACCESS_KEY_ID
                *************

                root@5976e1426a62:/app# echo $AWS_SECRET_ACCESS_KEY
                **************

        - The CMakeList.txt for each C++ app is always looking for these environment variables during compile time in order to predefine them as macros. So simply enable the OVERRIDE_AWS_CREDENTIALS #define in the C++ application main.c file in order to consume the keys.

            .. code-block:: cpp

                /* main.cpp */

                #define OVERRIDE_AWS_CREDENTIALS
                //#undef OVERRIDE_AWS_CREDENTIALS



2. Go to the desired AWS project
    For example, let's run the encryption project

    .. code-block:: bash

        root@5976e1426a62:/app/sandbox/aws# cd encryption
        root@5976e1426a62:/app/sandbox/aws/encryption#

2. Run Terraform
    Go to the terraform folder

    .. code-block:: bash

        root@5976e1426a62:/app/sandbox/aws/encryption# cd terraform
        root@5976e1426a62:/app/sandbox/aws/encryption/terraform#

    Create a secret.tfvars file with the user AWS credentials. This file will be consumed by terraform to access AWS

    .. code-block:: bash

        # secret.tfvars
        a_aws_user = {
            "access_key"  = "<ACCESS_KEY>",
            "secret_key" = "<SECRET_KEY>",
            "token" = "<TOKEN>"
        }

    Initialize terraform

    .. code-block:: bash

        root@5976e1426a62:../encryption/terraform# terraform init

    Apply terraform (create resources in AWS). Once completed, go to the AWS Console to verify that terraform create the desired resources

    .. code-block:: bash

        root@5976e1426a62:.../encryption/terraform# terraform apply -var-file="secret.tfvars"


    Destroy terraform (to remove AWS resources)

    .. code-block:: bash

        root@5976e1426a62:.../encryption/terraform# terraform destroy -var-file="secret.tfvars"

