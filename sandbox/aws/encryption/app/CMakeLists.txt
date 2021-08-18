# Define an executable
cmake_minimum_required(VERSION 3.16.3)
project(encryption)

#add_compile_definitions(OPENCV_VERSION=$ENV{ACCESS_KEY})


add_executable(encryption
        main.cpp)

# pre-define macros. For debugging and educational purposes.
target_compile_definitions(encryption PRIVATE
                ACCESS_KEY="$ENV{AWS_ACCESS_KEY_ID}"
                SECRET_KEY="$ENV{AWS_SECRET_ACCESS_KEY}")

# Define the libraries this project depends upon
find_package(AWSSDK REQUIRED COMPONENTS s3)

target_link_libraries(encryption
                      ${AWSSDK_LINK_LIBRARIES})
