# Locate the glfw library
# This module defines the following variables:
# GLFW_LIBRARIES, the name of the library;
# GLFW_INCLUDE_DIRS, where to find glfw include files.
# GLFW_FOUND, true if both the GLFW_LIBRARIES and GLFW_INCLUDE_DIRS have been found.
#
# To help locate the library and include file, you could define an environment variable called
# GLFW_ROOT which points to the root of the glfw library installation. This is pretty useful
# on a Windows platform.
#
#
# Usage example to compile an "executable" target to the glfw library:
#
# FIND_PACKAGE (glfw REQUIRED)
# INCLUDE_DIRECTORIES (${GLFW_INCLUDE_DIRS})
# ADD_EXECUTABLE (executable ${EXECUTABLE_SRCS})
# TARGET_LINK_LIBRARIES (executable ${GLFW_LIBRARIES})
#
# TODO:
# Allow the user to select to link to a shared library or to a static library.

#Search for the include file...
FIND_PATH(GLFW_INCLUDE_DIRS glfw/glfw3.h DOC "Path to GLFW3 include directory."
HINTS
$ENV{GLFW_ROOT}
PATH_SUFFIX include #For finding the include file under the root of the glfw expanded archive, typically on Windows.
PATHS
/usr/include/
/usr/local/include/
# By default headers are under GL subfolder
/usr/include/glfw
/usr/local/include/glfw
${CMAKE_INCLUDE_PATH}
${CMAKE_INCLUDE_PATH}/glfw

)

IF (CMAKE_CL_64)
	FIND_LIBRARY(GLFW_LIBRARIES DOC "Absolute path to GLFW library."
	NAMES glfw GLFW3.lib glfw3 libglfw
	HINTS
	$ENV{GLFW_ROOT}
	PATH_SUFFIXES lib/win32 #For finding the library file under the root of the glfw expanded archive, typically on Windows.
	PATHS 
	"${LIB_FOLDER}/glfw"
	)
ELSE()
	FIND_LIBRARY(GLFW_LIBRARIES DOC "Absolute path to GLFW library."
	NAMES glfw GLFW3.lib glfw3 libglfw3.a
	HINTS
	$ENV{GLFW_ROOT}
	PATH_SUFFIXES lib/win32 #For finding the library file under the root of the glfw expanded archive, typically on Windows.
	PATHS 
	"${LIB_FOLDER}/glfw"
	)
ENDIF()

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_LIBRARIES GLFW_INCLUDE_DIRS)
