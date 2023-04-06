# Define an executable
cmake_minimum_required(VERSION 3.16.3)
project(app)


add_executable(prototype
               main.cpp )

# Define the libraries this project depends upon
find_package(Creational REQUIRED COMPONENTS creational)

target_link_libraries(prototype
                      Creational::libcreational
                      boost_serialization)

