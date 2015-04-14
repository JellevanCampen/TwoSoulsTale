# FindGLFW
# Copyright (c) 2015 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- GLFW_FOUND : true if both the includes and libraries are found
# -- GLFW_INCLUDE_DIRS : location of the include files
# -- GLFW_LIBRARIES : required library files
# -- GLFW_DEFINITIONS : compiler switches required by the library
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : project directory where include files are located
# -- CMAKE_LIBRARY_PATH : project directory where lib files are located 
# -- GLFW_ROOT_DIR : root directory of GLFW (specified as CMake variable)
# -- ENV GLFW_ROOT : root directory of GLFW (specified as environment variable)
#
# Usage: 
# -- find_package(GLFW REQUIRED)
# -- if (GLFW_FOUND)
# --     include_directories(${GLFW_INCLUDE_DIRS})
# --     target_link_libraries(<project> ${GLFW_LIBRARIES})
# --     add_definitions${GLFW_DEFINITIONS})
# -- endif (GLFW_FOUND)

message(STATUS ">> Locating GLFW: ")

# Find on Windows
IF (WIN32)

	# ---- Include directories
	FIND_PATH( GLFW_INCLUDE_DIRS 
		NAMES 
			glfw3.h
		PATHS 
			${CMAKE_INCLUDE_PATH}
			${CMAKE_INCLUDE_PATH}/glfw
			${GLFW_ROOT_DIR}/include/GLFW
			$ENV{GLFW_ROOT}/include/GLFW
		DOC 
			"The include directory for GLFW"
	)
	
	# ---- Libraries
	FIND_LIBRARY( GLFW_LIBRARIES
		NAMES 
			glfw glfw3.lib glfw3 libglfw
		PATHS
			${CMAKE_LIBRARY_PATH}
			${CMAKE_LIBRARY_PATH}/glfw
			${GLFW_ROOT_DIR}/lib/win32
			$ENV{GLFW_ROOT}/lib/win32
		DOC 
			"The libraries for GLFW"
	)
	
ENDIF(WIN32)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARIES GLFW_INCLUDE_DIRS)