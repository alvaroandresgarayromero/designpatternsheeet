# Define an executable
cmake_minimum_required(VERSION 3.16.3)
project(app)


add_executable(builder
               main.cpp )

# Define the libraries this project depends upon
find_package(Creational REQUIRED COMPONENTS creational)

target_link_libraries(builder
                      Creational::libcreational)

message(STATUS "The BoostLIBRARIES are  ${CMAKE_FIND_LIBRARY_SUFFIXES}")

