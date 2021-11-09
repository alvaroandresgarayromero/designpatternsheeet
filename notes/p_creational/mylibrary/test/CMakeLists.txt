# Define an executable
project(test_app)


add_executable(test_app
               main.cpp )

target_link_libraries(test_app
                      libcreational
                      boost_serialization)
