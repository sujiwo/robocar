cmake_minimum_required(VERSION 2.6)
project(robocar_common)

set (CMAKE_BUILD_TYPE Debug)
set_property (GLOBAL 
	PROPERTY COMPILE_DEFINITIONS DEBUG=1
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

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
  LIBRARIES robocar_common
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

###########
## Build ##
###########

include_directories(
	include
 	${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
add_library(robocar_common STATIC
	src/HokuyoDriver.cpp
	src/Message.cpp
	src/MessageQueue.cpp
	src/hokuyo.cpp
	#src/IMUMessage.cpp
)


