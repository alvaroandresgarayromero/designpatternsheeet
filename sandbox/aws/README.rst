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
AWS C++ SDK for performing logical operations on the cloud resources.
The reason behind using Terraform for provisioning cloud resources is to
create a habit of using a SaaS that is cloud agnostic. Therefore,
each AWS project sub-directory will have their own terraform, and app folder.

- To begin, go to the desired AWS project

    .. code-block:: bash

        # for example, let's go to encryption
        root@5976e1426a62:/app/sandbox/aws# cd encryption
        root@5976e1426a62:/app/sandbox/aws/encryption#

- Run Terraform

    1. Go to the terraform folder

        .. code-block:: bash

            root@5976e1426a62:/app/sandbox/aws/encryption# cd terraform
            root@5976e1426a62:/app/sandbox/aws/encryption/terraform#

    2. Create a secret.tfvars file with the user AWS credentials
        This file will be consumed by terraform to access AWS

        .. code-block:: bash
            # secret.tfvars
            a_aws_user = {
                "access_key"  = "<ACCESS_KEY>",
                "secret_key" = "<SECRET_KEY>",
                "token" = "TOKEN"
            }

    3. Initialize terraform

        .. code-block:: bash

            root@5976e1426a62:..//encryption/terraform# terraform init

    4. Apply terraform (create resources in AWS)
        Once completed, go to the AWS Console to verify that terraform create the
        desired resources

        .. code-block:: bash

            root@5976e1426a62:.../encryption/terraform# terraform apply -var-file="secret.tfvars"


    5. Destroy terraform (to remove AWS resources)

        .. code-block:: bash

            root@5976e1426a62:.../encryption/terraform# terraform destroy -var-file="secret.tfvars"

