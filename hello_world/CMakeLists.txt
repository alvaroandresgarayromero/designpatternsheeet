cmake_minimum_required(VERSION 3.16.3)
project(build)

set(CMAKE_CXX_STANDARD 20)

# create executable, and name it $(PROJECT_NAME)
add_executable(${PROJECT_NAME} main.cpp)