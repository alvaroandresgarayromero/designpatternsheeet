Introduction
=============

Design Pattern cheatsheet was created as a way to study and collect code snippets of the
various SOLID design principles.
This repository follows the Creational, Structural, and Behavioral pattern components as a
baseline for the project structure.

Cheat Sheet
============

- `Overview  <docs/notes/overview/README.rst>`_
- `Creational  <docs/notes/p_creational/README.rst>`_
- `Structural  <docs/notes/p_structural/README.rst>`_
- `Behavioral  <docs/notes/p_behavioral/README.rst>`_

Getting Started
================

This workspace utilizes Docker to create a containerized service with all the required
libraries and dependencies to run the C++ applications. To get started, follow the three main steps

- Verify that Docker and Docker-Compose are installed.

.. code-block:: bash

    # this project used Docker version 20.10.5
    $ docker --version

    # this project used docker-compose version 1.29.1
    $ docker-compose --version


- In the root of the project, build the image and container

.. code-block:: bash

    $ docker-compose up


- Docker has been set up such that
    - Any new or existing files that are added/modified are automatically updated in the active container.
    - Container port address is exposed so you can connect to it from your host computer (ex: IDE editor. I've been using CLion, see their documentation on how to connect with a remote host)


Acknowledgement
================

- Design Pattern in Modern C++ course by Dmitri Nesteruk
- Design Patterns: Elements of Reausable Object-Oriented Software by (Gang of Four Book)
    - Erick Gamma
    - Richard Helm
    - Ralph Johson
    - John Vissides