################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.0.2)
project(t_rex_runner)

################################################################################
# Find packages and libraries
################################################################################
find_package(SDL2 REQUIRED)

################################################################################
# Build
################################################################################
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(t_rex_runner game_node.cpp)
target_link_libraries(t_rex_runner ${SDL2_LIBRARIES})