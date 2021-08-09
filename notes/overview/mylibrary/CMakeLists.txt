cmake_minimum_required(VERSION 3.16.3)

project(Overview)

# Define project library name
set(LIB_NAME_1 lib)
set(LIB_NAME_2 overview)
set(LIBRARY_NAME ${LIB_NAME_1}${LIB_NAME_2})


# Define variables
include(GNUInstallDirs) # defines the default install paths for Linux
set(TARGET_CONFIG_NAME ${PROJECT_NAME}Targets) # OverviewTargets.cmake
set(TARGET_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${LIB_NAME_2}) # <prefix>/lib/cmake/overview
set(HEADER_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME_2}) # <prefix>/lib/cmake/overview


#########################################################
# set up LIBRARY name (liboverview) and target settings
#########################################################
# create static library
add_library(${LIBRARY_NAME} STATIC
            src/Journal.cpp )


# inform Cmake where include files are located for
# BUILD_INTERFACE: build tree
# INSTALL_INTERFACE: install tree
target_include_directories(${LIBRARY_NAME}
                           PUBLIC
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # <prefix>/include
                           PRIVATE
                            src)

# Let Cmake create library target as liboverview.a
# instead of libliboverview.a
set_target_properties(${LIBRARY_NAME}
        PROPERTIES
        OUTPUT_NAME ${LIB_NAME_2}
        )

###############################
# export library TARGET file
###############################
# This makes the project importable from the Linux install directory
install(TARGETS
         ${LIBRARY_NAME} # marks (ie. commit) the target for export
        EXPORT
         ${TARGET_CONFIG_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   # destination for dynamic libraries
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}   # destination for executables
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} ) # destination for static libraries
install(EXPORT ${TARGET_CONFIG_NAME} # save target content into file (ie. push)
        FILE ${TARGET_CONFIG_NAME}.cmake
        NAMESPACE ${PROJECT_NAME}:: # package name is the project name from the root CmakeLists.txt
        DESTINATION ${TARGET_CONFIG_DIR} ) # store in proper install tree destination
install(DIRECTORY include/ # copy the header files to the proper destination
        DESTINATION ${HEADER_DIR} ) # store in proper install tree destination

message(STATUS "LIBRARY_NAME: ${LIBRARY_NAME}")
message(STATUS "PROJECT_NAME : ${PROJECT_NAME} ")

###################################################
# export CONFIG file for find_package() to work
# - Consumes TARGET file
# - Consumes other dependencies, if any
###################################################
include(CMakePackageConfigHelpers)
set(CONFIG_NAME_IN ${PROJECT_NAME}Config)
set(CONFIG_NAME_OUT ${PROJECT_NAME}Config)

configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/CMake/${CONFIG_NAME_IN}.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_NAME_OUT}.cmake
        INSTALL_DESTINATION ${TARGET_CONFIG_DIR} )

# Install all the helper files
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_NAME_OUT}.cmake
        DESTINATION ${TARGET_CONFIG_DIR} )

add_subdirectory(test)