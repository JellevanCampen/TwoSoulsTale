# FindirrKlang
# Copyright (c) 2015 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- IRRKLANG_FOUND : true if both the includes and libraries are found
# -- IRRKLANG_INCLUDE_DIRS : location of the include files
# -- IRRKLANG_LIBRARIES : required library files
# -- IRRKLANG_DEFINITIONS : compiler switches required by the library
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : project directory where include files are located
# -- CMAKE_LIBRARY_PATH : project directory where lib files are located 
# -- IRRKLANG_ROOT_DIR : root directory of IrrKlang (specified as CMake variable)
# -- ENV IRRKLANG_ROOT : root directory of IrrKlang (specified as environment variable)
#
# Usage: 
# -- find_package(irrKlang REQUIRED)
# -- if (IRRKLANG_FOUND)
# --     include_directories(${IRRKLANG_INCLUDE_DIRS})
# --     target_link_libraries(<project> ${IRRKLANG_LIBRARIES})
# --     add_definitions(${IRRKLANG_DEFINITIONS})
# -- endif (IRRKLANG_FOUND)

message(STATUS ">> Locating irrKlang: ")

# Find on Windows
IF (WIN32)

	# ---- Include directories
	FIND_PATH( IRRKLANG_INCLUDE_DIRS 
		NAMES 
			irrKlang.h
		PATHS 
			${CMAKE_INCLUDE_PATH}
			${CMAKE_INCLUDE_PATH}/irrklang
			${IRRKLANG_ROOT_DIR}/include
			$ENV{IRRKLANG_ROOT}/include 
		DOC 
			"The include directory for irrKlang"
	)
	
	# ---- Libraries
	FIND_LIBRARY( IRRKLANG_LIBRARIES
		NAMES 
			irrKlang.lib
		PATHS
			${CMAKE_LIBRARY_PATH}
			${CMAKE_LIBRARY_PATH}/irrklang
			${IRRKLANG_ROOT_DIR}/lib
			$ENV{IRRKLANG_ROOT}/lib 
		DOC 
			"The libraries for irrKlang"
	)
	
ENDIF(WIN32)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IRRKLANG DEFAULT_MSG IRRKLANG_LIBRARIES IRRKLANG_INCLUDE_DIRS)