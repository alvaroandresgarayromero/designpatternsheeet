# Define an executable
add_executable(apps
        main.cpp )

# Define the libraries this project depends upon
target_link_libraries(apps
                        boost)

include(PrintVariables.cmake)
print_variables()