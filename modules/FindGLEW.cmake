# FindGLEW
# Copyright (c) 2015 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- GLEW_FOUND : true if both the includes and libraries are found
# -- GLEW_INCLUDE_DIRS : location of the include files
# -- GLEW_LIBRARIES : required library files
# -- GLEW_DEFINITIONS : compiler switches required by the library
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : project directory where include files are located
# -- CMAKE_LIBRARY_PATH : project directory where lib files are located 
# -- GLEW_ROOT_DIR : root directory of GLEW (specified as CMake variable)
# -- ENV GLEW_ROOT : root directory of GLEW (specified as environment variable)
#
# Usage: 
# -- find_package(GLEW REQUIRED)
# -- if (GLEW_FOUND)
# --     include_directories(${GLEW_INCLUDE_DIRS})
# --     target_link_libraries(<project> ${GLEW_LIBRARIES})
# --     add_definitions(${GLEW_DEFINITIONS})
# -- endif (GLEW_FOUND)

message(STATUS ">> Locating GLEW: ")

# Find on Windows
IF (WIN32)

	# ---- Include directories
	FIND_PATH( GLEW_INCLUDE_DIRS 
		NAMES 
			glew.h
		PATHS 
			${CMAKE_INCLUDE_PATH}
			${CMAKE_INCLUDE_PATH}/glew
			${GLEW_ROOT_DIR}/include/GL
			$ENV{GLEW_ROOT}/include/GL 
		DOC 
			"The include directory for GLEW"
	)
	
	# ---- Libraries
	FIND_LIBRARY( GLEW_LIBRARIES
		NAMES 
			glew glew32 glew32s
		PATHS
			${CMAKE_LIBRARY_PATH}
			${CMAKE_LIBRARY_PATH}/glew
			${GLEW_ROOT_DIR}/lib
			$ENV{GLEW_ROOT}/lib 
		DOC 
			"The libraries for GLEW"
	)
	
ENDIF(WIN32)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_LIBRARIES GLEW_INCLUDE_DIRS)