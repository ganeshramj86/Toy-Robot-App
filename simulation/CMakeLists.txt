cmake_minimum_required(VERSION 3.13)
project(simulation)

#Define GNU standard installation directories
include( GNUInstallDirs )

add_executable(simulation simulation.cpp)

#Link from installed packages
target_link_libraries( simulation toyrobot)

add_custom_target(copy_siminputs
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-siminputs.cmake
)
add_dependencies(simulation copy_siminputs)