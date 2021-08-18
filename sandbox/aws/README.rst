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

1. To begin, AWS credentials need to be configure inside the docker container
    Using AWS specific environment variables (note this also overrides any credentials/configuration file, if any)
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

        - Terraform and the AWS C++ SDK will now use these environment variables for authentication. Defaults to US_EAST_1


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

    Initialize terraform

    .. code-block:: bash

        root@5976e1426a62:../encryption/terraform# terraform init

    Apply terraform (create resources in AWS). Once completed, go to the AWS Console to verify that terraform create the desired resources

    .. code-block:: bash

        root@5976e1426a62:.../encryption/terraform# terraform apply


    Destroy terraform (to remove AWS resources)

    .. code-block:: bash

        root@5976e1426a62:.../encryption/terraform# terraform destroy

