cmake_minimum_required(VERSION 2.8.3)
project(dcart_exekutor)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  actionlib
  move_base_msgs
  roscpp
  std_msgs
  action_exekutor
)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES dcart_exekutor
  CATKIN_DEPENDS actionlib move_base_msgs roscpp std_msgs action_exekutor
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
add_library(dcart_exekutor
  src/dcart_exekutor.cpp
)

## Declare a cpp executable
add_executable(dcart_exekutor_node src/dcart_exekutor_node.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(dcart_exekutor
  ${catkin_LIBRARIES}
)

target_link_libraries(dcart_exekutor_node
  ${catkin_LIBRARIES}
  dcart_exekutor
  peiskernel_mt
)