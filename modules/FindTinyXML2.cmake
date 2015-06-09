# FindTinyXML2
# Copyright (c) 2015 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- TINYXML2_FOUND : true if both the includes and libraries are found
# -- TINYXML2_INCLUDE_DIRS : location of the include files
# -- TINYXML2_LIBRARIES : required library files
# -- TINYXML2_DEFINITIONS : compiler switches required by the library
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : project directory where include files are located
# -- CMAKE_LIBRARY_PATH : project directory where lib files are located 
# -- TINYXML2_ROOT_DIR : root directory of TinyXML2 (specified as CMake variable)
# -- ENV TINYXML2_ROOT : root directory of TinyXML2 (specified as environment variable)
#
# Usage: 
# -- find_package(TINYXML2 REQUIRED)
# -- if (TINYXML2_FOUND)
# --     include_directories(${TINYXML2_INCLUDE_DIRS})
# --     target_link_libraries(<project> ${TINYXML2_LIBRARIES})
# --     add_definitions${TINYXML2_DEFINITIONS})
# -- endif (TINYXML2_FOUND)

message(STATUS ">> Locating TinyXML2: ")

# Find on Windows
IF (WIN32)

	# ---- Include directories
	FIND_PATH( TINYXML2_INCLUDE_DIRS 
		NAMES 
			tinyxml2
		PATHS 
			${CMAKE_INCLUDE_PATH}
			${CMAKE_INCLUDE_PATH}/tinyxml2
			${TINYXML2_ROOT_DIR}
			$ENV{TINYXML2_ROOT}
		DOC 
			"The include directory for TinyXML2"
	)
	
	# ---- Libraries
	FIND_LIBRARY( TINYXML2_LIBRARIES
		NAMES 
			tinyxml2
		PATHS
			${CMAKE_LIBRARY_PATH}
			${CMAKE_LIBRARY_PATH}/tinyxml2
			${TINYXML2_ROOT_DIR}/build/Debug
			$ENV{TINYXML2_ROOT}/build/Debug
		DOC 
			"The libraries for TinyXML2"
	)
	
ENDIF(WIN32)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TINYXML2 DEFAULT_MSG TINYXML2_INCLUDE_DIRS TINYXML2_LIBRARIES)