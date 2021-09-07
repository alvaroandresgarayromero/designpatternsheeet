# Define an executable
cmake_minimum_required(VERSION 3.16.3)
project(app)

set(LIBRARY_NAME app_library)

#------ create custom static library inside build tree -----#
# and inform Cmake where include files are located for
add_library(${LIBRARY_NAME} STATIC
        src/AwsDemo.cpp
        src/AwsDemoBuilder.cpp
        src/AwsDemoSqsBuilder.cpp
        src/AwsDemoS3Builder.cpp
        src/AwsDemoSnsBuilder.cpp)
target_include_directories(${LIBRARY_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # <prefix>/include
        )

# Define the libraries from install tree that this project requires
find_package(AWSSDK REQUIRED COMPONENTS s3 sqs sns)


#-------create executable ------#
add_executable(${PROJECT_NAME} app/main.cpp)

#------- define pre-define macros for executable -----#
target_compile_definitions(${PROJECT_NAME} PRIVATE
                ACCESS_KEY="$ENV{AWS_ACCESS_KEY_ID}"
                SECRET_KEY="$ENV{AWS_SECRET_ACCESS_KEY}")

#------- link libraries to executable -----#
target_link_libraries(${LIBRARY_NAME}
        ${AWSSDK_LINK_LIBRARIES} )


target_link_libraries(${PROJECT_NAME}
                      ${AWSSDK_LINK_LIBRARIES}
                      ${LIBRARY_NAME})
