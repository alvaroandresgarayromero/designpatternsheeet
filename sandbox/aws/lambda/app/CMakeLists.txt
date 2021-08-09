# Define an executable
cmake_minimum_required(VERSION 3.16.3)
project(lambda)


add_executable(lambda
        main.cpp)

# Define the libraries this project depends upon
find_package(AWSSDK REQUIRED COMPONENTS s3)

target_link_libraries(lambda
                      ${AWSSDK_LINK_LIBRARIES})
