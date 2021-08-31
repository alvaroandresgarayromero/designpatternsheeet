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

                root@5976e1426a62:/app# echo $AWS_DEFAULT_REGION
                **************

        - Terraform and the AWS C++ SDK will now use these environment variables for authentication.


    OR use the aws CLI to set the aws credentials

    .. code-block:: bash

        $ aws configure
        AWS Access Key ID [None]: ***************
        AWS Secret Access Key [None]: ***************
        Default region name [None]: *****
        Default output format [None]: json
