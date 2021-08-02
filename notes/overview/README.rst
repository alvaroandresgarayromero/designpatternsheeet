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


Single Responsibility Principle
---------------------------------

A class should have a single reason to change.
It should not take other responsibilities


Open Closed Principle
----------------------

A class should be open for extension (inheritance),
but closed for modification (about touch code that has already been written)

Liskov Substitution Principle
------------------------------

Based class pointers or reference to the derived class
shall get the correct methods


Interface Segregation Principle
--------------------------------

Don't create interfaces that are too large


Dependency Inversion Principle
--------------------------------

High level modules should not depend on low level modules.
Both should depend on abstraction.