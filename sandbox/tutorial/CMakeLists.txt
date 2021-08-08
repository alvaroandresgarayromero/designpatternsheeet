cmake_minimum_required(VERSION 3.16.3)
project(tutorial)

set(CMAKE_CXX_STANDARD 20)

# Include Boost as an imported target
find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost
             PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})


get_property(value2 TARGET boost INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "INTERFACE_INCLUDE_DIRECTORIES: ${value}")
message(STATUS "INTERFACE_INCLUDE_DIRECTORIES: ${value2}")
