Introduction
=============

Design Pattern cheatsheet was created as a way to study and collect code snippets of the
various SOLID design principles.
This repository follows the Creational, Structural, and Behavioral pattern components as a
baseline for the project structure.

Cheat Sheet
============

- `Overview <notes/overview/README.rst>`_
- `Creational <notes/p_creational/README.rst>`_
- `Structural <notes/p_structural/README.rst>`_
- `Behavioral <notes/p_behavioral/README.rst>`_

Getting Started
================

This workspace utilizes Docker to create a containerized service with all the required
libraries and dependencies to run the C++ applications. To get started, follow the steps below

- Install Docker:
    Verify that Docker and Docker-Compose are installed.

    .. code-block:: bash

        # this project used Docker version 20.10.5
        $ docker --version

        # this project used docker-compose version 1.29.1
        $ docker-compose --version

- Build image, and run Docker container:
    Any new or existing files that are added/modified are automatically updated in the active container or vice-versa.

    .. code-block:: bash

        # This may take a couple of minutes when running for the first time
        $ sudo docker-compose up

- Running C++ application with the CLI:
    Enter Docker Container

    .. code-block:: bash

        # the numbers on root@**** is your unique Container ID
        $ sudo docker exec -it cpp_container_latest /bin/bash
        root@5976e1426a62:/app#

    Generate the build files from the test workspace.
    Note that each workspace will have their own CMakeLists.txt to keep them independent.

    .. code-block:: bash

        # the test workspace is in the hello_world directory
        root@5976e1426a62:/app# cd hello_world/
        root@5976e1426a62:/app/hello_world# cmake -S . -B out

    Generate the executable file. The executable file will be named "build"

    .. code-block:: bash

        root@5976e1426a62:/app/hello_world# cd out/
        root@5976e1426a62:/app/hello_world/out# make

    Run the executable file.

    .. code-block:: bash

        # Docker ID will printed since application is been
        # ran from the Docker Container with ID 5976e1426a62
        root@5976e1426a62:/app/hello_world/out# ./build
        Hello from 5976e1426a62

- Running C++ with an IDE
    SSH Port 22 from inside the docker container is exposed
    to Port 2222 inside the host (see docker-compose.yml)
    This allows the host to shh into the remote host ( docker container)
    from any IDE.
    (ex: I've been using CLion, see their documentation on
    how to connect with a remote host)




Acknowledgement
================

- Design Pattern in Modern C++ course by Dmitri Nesteruk
- Design Patterns: Elements of Reausable Object-Oriented Software by (Gang of Four Book)
    - Erick Gamma
    - Richard Helm
    - Ralph Johson
    - John Vissides