cmake_minimum_required(VERSION 3.13)
project(toyrobot)

#Define GNU standard installation directories
include( GNUInstallDirs )

# Bring the headers
include_directories(include)

# Can manually add the sources using the set command as follows:
set(SOURCES src/toyrobot.cpp src/commandhandler.cpp src/config.cpp)

# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

# Generate the static library from the sources
add_library(toyrobot STATIC ${SOURCES} ${HEADERS})

target_include_directories( toyrobot PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )