.. meta::
    :description lang=en: SOLID Design Principles
    :keywords: C++, SOLID

==========
Overview
==========

.. contents:: Table of Contents
    :backlinks: none

Introduction
--------------

Design Pattern is the design of software architectural approaches.
These approaches can be summarized by 5 main principles known
as SOLID design principles

- Single Responsibility Principle

    A class should have a single reason to change.
    It should not take other responsibilities

- Open Closed Principle

    A class should be open for extension (inheritance),
    but closed for modification (about touch code that has already been written)

- Liskov Substitution Principle

    Based class pointers or reference to the derived class
    shall get the correct methods

- Interface Segregation Principle

    Don't create interfaces that are too large

- Dependency Inversion Principle

    High level modules should not depend on low level modules.
    Both should depend on abstraction.

Getting Started
-----------------

1. Create Library Package
    Design Patterns are implementation software that are very
    common in libraries. This project simulates this by creating a library package
    target named "Overview::liboverview",
    which has all the design pattern implementations, and dependencies.


    The steps below show how to create the package library for this project

    .. code-block:: bash

        # 'mylibrary' directory has all the design pattern implementations
        /app/notes/overview# cd mylibrary/

        # create directory to store the build files
        /app/notes/overview/mylibrary# mkdir out
        /app/notes/overview/mylibrary# cd out

        # create build files
        /app/notes/overview/mylibrary/out# cmake ..

        # create library, package it, and export to install tree
        /app/notes/overview/mylibrary/out# make install



2. Compile application
    The user (developers) then consume their desired libraries within their own application.
    This project simulates this by creating 5 application projects for each
    SOLID principle. These applications look for and consume the "Overview" package library
    in order to consume them, and show their functionalities.

    The steps below show how to create the executable files for the 5 applications.

    .. code-block:: bash

        # 'app' directory has the applications
        /app/notes/overview# cd app/

        # create directory to store the build files
        /app/notes/overview/app# mkdir out
        /app/notes/overview/app# cd out

        # create build files
        /app/notes/overview/app/out# cmake ..

        # create executable files for each application
        /app/notes/overview/app/out# make

        # for example, to run the "dependency_inversion_principle"
        /app/notes/overview/app/out# cd dependency_inversion_principle
        /app/notes/overview/app/out/dependency_inversion_principle# ./dependency_inversion_principle
