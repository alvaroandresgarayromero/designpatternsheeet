# Define an executable
cmake_minimum_required(VERSION 3.16.3)
project(lambda)


add_executable(${PROJECT_NAME}
        main.cpp)

# Define the libraries this project depends upon
find_package(AWSSDK REQUIRED COMPONENTS s3)
find_package(aws-lambda-runtime REQUIRED)

target_link_libraries(${PROJECT_NAME}
                      ${AWSSDK_LINK_LIBRARIES}
                      AWS::aws-lambda-runtime)

# to package the executable along with all its dependencies
# make aws-lambda-package-<${PROJECT_NAME}>
aws_lambda_package_target(${PROJECT_NAME})
