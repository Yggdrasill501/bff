cmake_minimum_required(VERSION 3.10)

project(bff)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Qt 6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(${PROJECT_SOURCE_DIR}/src)

# Source files
set(SOURCES
    src/main.cpp
    src/controller.cpp
    src/icons.cpp
)

# Header files
set(HEADERS
    src/controller.h
    src/icons.h
)

qt6_wrap_cpp(MOC_SOURCES ${HEADERS})

# Resource files
qt6_add_resources(RESOURCES resources.qrc)

# Add executable
add_executable(bff ${SOURCES} ${MOC_SOURCES} ${RESOURCES})

# Link Qt 6 libraries
target_link_libraries(bff Qt6::Core Qt6::Gui Qt6::Widgets)
