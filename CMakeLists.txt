################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.0.2)
project(t_rex_runner)

################################################################################
# Find catkin packages and libraries for catkin and system dependencies
################################################################################
find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
)

find_package(SDL2 REQUIRED)

################################################################################
# Declare catkin specific configuration to be passed to dependent projects
################################################################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
)

################################################################################
# Build
################################################################################
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIRS}
)

add_executable(t_rex_runner src/game_node.cpp)
target_link_libraries(t_rex_runner ${catkin_LIBRARIES} ${SDL2_LIBRARIES})