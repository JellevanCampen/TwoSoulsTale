# FindFreeImage
# Copyright (c) 2015 Jelle van Campen
# Redistribution and use allowed according to the terms of the MIT license. 
#
# Defines: 
# -- FREEIMAGE_FOUND : true if both the includes and libraries are found
# -- FREEIMAGE_INCLUDE_DIRS : location of the include files
# -- FREEIMAGE_LIBRARIES : required library files
# -- FREEIMAGE_DEFINITIONS : compiler switches required by the library
#
# Makes use of:
# -- CMAKE_INCLUDE_PATH : project directory where include files are located
# -- CMAKE_LIBRARY_PATH : project directory where lib files are located 
# -- FREEIMAGE_ROOT_DIR : root directory of FreeImage (specified as CMake variable)
# -- ENV FREEIMAGE_ROOT : root directory of FreeImage (specified as environment variable)
#
# Usage: 
# -- find_package(FreeImage REQUIRED)
# -- if (FREEIMAGE_FOUND)
# --     include_directories(${FREEIMAGE_INCLUDE_DIRS})
# --     target_link_libraries(<project> ${FREEIMAGE_LIBRARIES})
# --     add_definitions(${FREEIMAGE_DEFINITIONS})
# -- endif (FREEIMAGE_FOUND)

message(STATUS ">> Locating irrKlang: ")

# Find on Windows
IF (WIN32)

	# ---- Include directories
	FIND_PATH( FREEIMAGE_INCLUDE_DIRS 
		NAMES 
			FreeImage.h
		PATHS 
			${CMAKE_INCLUDE_PATH}
			${CMAKE_INCLUDE_PATH}/freeimage
			${FREEIMAGE_ROOT_DIR}/include
			$ENV{FREEIMAGE_ROOT}/include 
		DOC 
			"The include directory for FreeImage"
	)
	
	# ---- Libraries
	FIND_LIBRARY( FREEIMAGE_LIBRARIES
		NAMES 
			FreeImage.lib
		PATHS
			${CMAKE_LIBRARY_PATH}
			${CMAKE_LIBRARY_PATH}/FreeImage
			${FREEIMAGE_ROOT_DIR}/lib
			$ENV{FREEIMAGE_ROOT}/lib 
		DOC 
			"The libraries for FreeImage"
	)
	
ENDIF(WIN32)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FREEIMAGE DEFAULT_MSG FREEIMAGE_LIBRARIES FREEIMAGE_INCLUDE_DIRS)