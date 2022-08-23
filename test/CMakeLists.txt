cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)

project(catch-tdd-test)

#Define GNU standard installation directories
include( GNUInstallDirs )

#set(WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CMAKE_CURRENT_LIST_DIR})


add_executable(test_command_handler test_command_handler.cpp)
add_executable(test_toyrobot test_toyrobot.cpp)
add_executable(integration_test integration_test.cpp)

#Link from installed packages
target_link_libraries( test_command_handler toyrobot Catch )
target_link_libraries( test_toyrobot toyrobot Catch )
target_link_libraries( integration_test toyrobot Catch )

enable_testing()
add_test(NAME CommandFormatTest COMMAND test_command_handler)
add_test(NAME CommandExecutionTest COMMAND test_toyrobot)
add_test(NAME IntegrationTest COMMAND integration_test)

# catch_discover_tests(test_command_handler)
# catch_discover_tests(test_toyrobot)
# catch_discover_tests(integration_test)

#configure_file(input_integration_test1.txt input_integration_test1.txt COPYONLY)

add_custom_target(copy_inputs
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-inputs.cmake
)
add_dependencies(integration_test copy_inputs)
