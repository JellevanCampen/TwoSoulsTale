#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_DIRS
# GLEW_LIBRARIES
# 

IF (WIN32)
	FIND_PATH( GLEW_INCLUDE_DIRS glew/glew.h
		${CMAKE_INCLUDE_PATH}
		${GLEW_ROOT_DIR}/include
		DOC "The directory where glew/glew.h resides")

	IF (CMAKE_CL_64)
		FIND_LIBRARY( GLEW_LIBRARIES
			NAMES glew GLEW glew32 glew32s
			PATHS			
			"${LIB_FOLDER}/glew"
			DOC "The GLEW library (64-bit)"
		)
	ELSE()
		FIND_LIBRARY( GLEW_LIBRARIES
			NAMES glew GLEW glew32 glew32s
			PATHS
			"${LIB_FOLDER}/glew"
			DOC "The GLEW library"
		)
	ENDIF()
ELSE (WIN32)
	FIND_PATH( GLEW_INCLUDE_DIRS glew/glew.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		${GLEW_ROOT_DIR}/include
		DOC "The directory where glew/glew.h resides")

	FIND_LIBRARY( GLEW_LIBRARIES
		NAMES GLEW glew
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		${GLEW_ROOT_DIR}/lib
		DOC "The GLEW library")
ENDIF (WIN32)

# Show a confirmation (or error) message, sets the FOUND flag, and handle the REQUIRED attribute
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_LIBRARIES GLEW_INCLUDE_DIRS)