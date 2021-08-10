Introduction
=============

Design Pattern cheatsheet was created as a way to study and collect code snippets of the
various SOLID design principles.
This repository follows the Creational, Structural, and Behavioral software design components as a
baseline for the project structure.

Cheat Sheet
=============

This workspace utilizes Docker to create a containerized service with all the required
dependencies, and CMake to compile the C++ applications.

- The "notes" directory is where the "Design Pattern" code base is maintained.
    - `Overview <notes/overview>`_
    - `Creational <notes/p_creational>`_
    - `Structural <notes/p_structural>`_
    - `Behavioral <notes/p_behavioral>`_

- The "sandbox" directory is where the experimental code is maintained.
    - `AWS S3 with server-side encryption <sandbox/aws>`_
    - `AWS Lambda with AWS SQS <sandbox/aws>`_

I highly recommend completing the 'Getting Started' section below
prior to diving into the "notes" and "sandbox" directories.

Getting Started
================

To get started, let's run a simple C++ application within
a Docker container. The app will print out the device hostname
from where its been executed on the terminal.

1. Install Docker:
    Verify that Docker and Docker-Compose are installed.

    .. code-block:: bash

        # this project used Docker version 20.10.5
        $ docker --version

        # this project used docker-compose version 1.29.1
        $ docker-compose --version

2. Build image, and run Docker container:
    This will take some minutes (~30 minutes) during the first time

    .. code-block:: bash

        # Executes docker container
        $ sudo docker-compose up

        # Open a new terminal to verify the active docker container is running
        # Note the container ID as we will use it below to verify the C++ test
        # app is running within the container.
        $ sudo docker container ls
        CONTAINER ID   IMAGE              COMMAND                  CREATED       STATUS          PORTS                    NAMES
        5976e1426a62   cpp_image_latest   "/usr/sbin/sshd -D -…"   3 weeks ago   Up 14 minutes   127.0.0.1:2222->22/tcp   cpp_container_latest


3. Running C++ application with the CLI:
    The instructions below shows you how to run the
    C++ application within the docker container through its
    command line interface (CLI).

    See the next step for tips on how to run from an IDE as well.

    Enter Docker Container

    .. code-block:: bash

        # the numbers on root@**** is your unique Container ID
        $ sudo docker exec -it cpp_container_latest /bin/bash
        root@5976e1426a62:/app#

    Generate the build files from the test application.

    .. code-block:: bash

        # the test application is in the hello_world directory
        root@5976e1426a62:/app# cd hello_world/

        # create folder to store the build files
        root@5976e1426a62:/app/hello_world# mkdir out
        root@5976e1426a62:/app/hello_world# cd out

        # generate the build files
        root@5976e1426a62:/app/hello_world/out# cmake ..

    Generate the executable binary file. The test app executable file created is "build"

    .. code-block:: bash

        root@5976e1426a62:/app/hello_world/out# make

    Run the executable file.

    .. code-block:: bash

        # The test app will print the hostname from where its executed.
        # In this example, the Docker Container ID 5976e1426a62 is the hostname for the container.
        root@5976e1426a62:/app/hello_world/out# ./build
        Hello from 5976e1426a62

3. Running C++ with an IDE
    The instructions below shows you how to run the
    C++ application within the docker container from your host computer IDE.

    - Option 1: Some IDEs have Docker support. Check their documentation on how to connect to the container.
    - Option 2: Some IDEs don't have Docker support, but have remote host SSH connection support.
        - This container has exposed SSH Port 22 to Port 2222 for the host to connect to the container, (see docker-compose.yml for the port, and DockerFile for the user credentials).
        - As of 07/12/2021, remote host connection with Clion IDE works (see their documentation on how to connect to remote host: https://blog.jetbrains.com/clion/2020/01/using-docker-with-clion/#creating-a-docker-container-for-use-with-clion)

    Build and run the test application to verify that the host computer IDE is running the C++ application
    within the Docker Container. The output should be the active Docker Container ID

    .. code-block:: bash

        # test application path: .../hello_world/main.cpp

        # Docker ID will printed since application is been
        # executed from the Docker Container with ID 5976e1426a62
        Hello from 5976e1426a62


Acknowledgement
================

- Design Pattern in Modern C++ course by Dmitri Nesteruk
- Design Patterns: Elements of Reausable Object-Oriented Software by (Gang of Four Book)
    - Erick Gamma
    - Richard Helm
    - Ralph Johson
    - John Vissides
- The Coding Nest (Basic CMake, part 2: libraries) by Martin Hořeňovský
- AWS Developer Tools Blog: Using CMake Exports with the AWS SDK for C++ by Jonathan Henson
