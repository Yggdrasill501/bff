cmake_minimum_required(VERSION 3.10)

# Set your project name
project(bff)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Source files
set(SOURCES
    src/main.cpp
    src/controller.cpp
    src/icons.cpp
)

# Add executable
add_executable(bff ${SOURCES})

# Link ncurses library
target_link_libraries(bff ncurses)
