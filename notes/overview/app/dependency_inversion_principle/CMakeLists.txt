# Define an executable
cmake_minimum_required(VERSION 3.16.3)
project(app)


add_executable(dependency_inversion_principle
               main.cpp )


# Define the libraries this project depends upon

find_package(Overview REQUIRED COMPONENTS overview)

target_link_libraries(dependency_inversion_principle
                      Overview::liboverview)

message(STATUS "The BoostLIBRARIES are  ${CMAKE_FIND_LIBRARY_SUFFIXES}")

