cmake_minimum_required(VERSION 3.16.3)
project(encryption)

set(CMAKE_CXX_STANDARD 20)

# create "boost" target
# INTERFACE : can be consumed by other cmake files, but not used in this cmake file
# IMPORTED: this library is located outside the project
# PROPERTY: Like an enum - variable : value
find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)


#set_property(TARGET boost PROPERTY
#             INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

add_subdirectory(app)



#find_package(Boost REQUIRED)

#if(Boost_FOUND)
    #include_directories(${Boost_INCLUDE_DIRS})
#endif()

#if(NOT Boost_FOUND)
    #message(STATUS "Boostpackage not found")
#endif()

# create executable, and name it $(PROJECT_NAME)
#add_executable(${PROJECT_NAME} main.cpp)

#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

