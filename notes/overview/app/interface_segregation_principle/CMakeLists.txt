# Define an executable
cmake_minimum_required(VERSION 3.16.3)
project(app)


add_executable(interface_segregation_principle
               main.cpp )


# Define the libraries this project depends upon
find_package(Overview REQUIRED)

target_link_libraries(interface_segregation_principle
                      Overview::liboverview)
