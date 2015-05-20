# FindBox2D
# Copyright (c) 2015 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- BOX2D_FOUND : true if both the includes and libraries are found
# -- BOX2D_INCLUDE_DIRS : location of the include files
# -- BOX2D_LIBRARIES : required library files
# -- BOX2D_DEFINITIONS : compiler switches required by the library
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : project directory where include files are located
# -- CMAKE_LIBRARY_PATH : project directory where lib files are located 
# -- BOX2D_ROOT_DIR : root directory of box2d (specified as CMake variable)
# -- ENV BOX2D_ROOT : root directory of box2d (specified as environment variable)
#
# Usage: 
# -- find_package(BOX2D REQUIRED)
# -- if (BOX2D_FOUND)
# --     include_directories(${BOX2D_INCLUDE_DIRS})
# --     target_link_libraries(<project> ${BOX2D_LIBRARIES})
# --     add_definitions${BOX2D_DEFINITIONS})
# -- endif (BOX2D_FOUND)

message(STATUS ">> Locating Box2D: ")

# Find on Windows
IF (WIN32)

	# ---- Include directories
	FIND_PATH( BOX2D_INCLUDE_DIRS 
		NAMES 
			Box2D.h
		PATHS 
			${CMAKE_INCLUDE_PATH}
			${CMAKE_INCLUDE_PATH}/box2d
			${BOX2D_ROOT_DIR}/Box2D/Box2D
			$ENV{BOX2D_ROOT}/Box2D/Box2D
		DOC 
			"The include directory for Box2D"
	)
	
	# ---- Libraries
	FIND_LIBRARY( BOX2D_LIBRARIES
		NAMES 
			Box2D.lib
		PATHS
			${CMAKE_LIBRARY_PATH}
			${CMAKE_LIBRARY_PATH}/box2d
			${BOX2D_ROOT_DIR}/Box2D/Build/Box2D/Debug
			$ENV{BOX2D_ROOT}/Box2D/Build/Box2D/Debug 
		DOC 
			"The libraries for Box2D"
	)
	
ENDIF(WIN32)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(BOX2D DEFAULT_MSG BOX2D_INCLUDE_DIRS BOX2D_LIBRARIES)