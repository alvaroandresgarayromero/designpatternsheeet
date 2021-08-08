# A helper function to use when developing/debugging cmake files
#
# Copy this file to the desired directory, and then add the code snipped below:
# include(PrintVariables.cmake)
# print_variables()

function(print_variables)
    message(STATUS "The CMake SOURCE directory is ${CMAKE_SOURCE_DIR}")
    message(STATUS "The Cmake BINARY directory is ${CMAKE_BINARY_DIR}")
    message(STATUS "The SOURCE directory of the '${PROJECT_NAME}' project is ${PROJECT_SOURCE_DIR}")
    message(STATUS "The BINARY directory of the '${PROJECT_NAME}' project is ${PROJECT_BINARY_DIR}")
    message(STATUS "The version of the current project is ${PROJECT_VERSION}")
    message(STATUS "The current SOURCE directory is ${CMAKE_CURRENT_SOURCE_DIR}")
    message(STATUS "The current BINARY directory is ${CMAKE_CURRENT_BINARY_DIR}")
    message(STATUS "The current script file is ${CMAKE_CURRENT_LIST_FILE}")
    message(STATUS "The current script directory is ${CMAKE_CURRENT_LIST_DIR}")
    message(STATUS " ")
endfunction()