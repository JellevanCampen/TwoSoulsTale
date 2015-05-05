# FindGLM
# Copyright (c) 2015 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- GLM_FOUND : true if both the includes and libraries are found
# -- GLM_INCLUDE_DIRS : location of the include files
# -- GLM_LIBRARIES : required library files
# -- GLM_DEFINITIONS : compiler switches required by the library
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : project directory where include files are located
# -- CMAKE_LIBRARY_PATH : project directory where lib files are located 
# -- GLM_ROOT_DIR : root directory of GLM (specified as CMake variable)
# -- ENV GLM_ROOT : root directory of GLM (specified as environment variable)
#
# Usage: 
# -- find_package(GLM REQUIRED)
# -- if (GLM_FOUND)
# --     include_directories(${GLM_INCLUDE_DIRS})
# --     target_link_libraries(<project> ${GLM_LIBRARIES})
# --     add_definitions${GLM_DEFINITIONS})
# -- endif (GLM_FOUND)

message(STATUS ">> Locating GLM: ")

# Find on Windows
IF (WIN32)

	# ---- Include directories
	FIND_PATH( GLM_INCLUDE_DIRS 
		NAMES 
			glm.hpp
		PATHS 
			${CMAKE_INCLUDE_PATH}
			${CMAKE_INCLUDE_PATH}/glm
			${GLM_ROOT_DIR}/include/GLM
			$ENV{GLM_ROOT}/include/GLM
		DOC 
			"The include directory for GLM"
	)
	
ENDIF(WIN32)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIRS)