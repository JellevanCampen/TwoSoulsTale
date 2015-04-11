cmake_minimum_required (VERSION 2.6)

################################################################
# Project and settings                                         #
################################################################

project (TwoSoulsTale)

# Project paths
set(CMAKE_PROJECT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/modules" ${CMAKE_MODULE_PATH}) # Custom CMake modules as well as the default CMake modules
set(CMAKE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# Switch to the x86 or x64 versions of the DLL and LIB folders
IF(CMAKE_EXE_LINKER_FLAGS MATCHES "x64")
	message(STATUS "Using x64 versions of DLLs and libraries")
	set (DLL_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/dll/x64)     
	set (LIB_FOLDER ${CMAKE_LIBRARY_PATH}/x64)
ELSE()
	message(STATUS "Using x86 versions of DLLs and libraries")
	set (DLL_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/dll/x86)
	set (LIB_FOLDER ${CMAKE_LIBRARY_PATH}/x86)
ENDIF()

# Add the main executable
add_executable(TwoSoulsTale src/main.cpp)



################################################################
# External libraries                                           #
################################################################

include_directories(include)

# OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${OPENGL_LIBRARIES})
endif (OPENGL_FOUND)

# GLFW
find_package(GLFW REQUIRED)
if (GLFW_FOUND)
	include_directories(${GLFW_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${GLFW_LIBRARIES})
endif (GLFW_FOUND)

# GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${GLEW_LIBRARIES})
endif (GLEW_FOUND)



################################################################
# Engine library                                               #
################################################################

# General Components
set(SRC_ENGINE_GAME 
	"src/engine/Game.hpp"
	"src/engine/Game.cpp"
)
source_group(Engine FILES ${SRC_ENGINE_GAME})

# Debugging Components
set(SRC_ENGINE_DEBUGGING 
	"src/engine/debugging/LoggingManager.hpp"
	"src/engine/debugging/LoggingManager.cpp"
)
source_group(Engine\\Debugging FILES ${SRC_ENGINE_DEBUGGING})

# Graphics Components
set(SRC_ENGINE_GRAPHICS 
	"src/engine/graphics/GraphicsManager.hpp"
	"src/engine/graphics/GraphicsManager.cpp"
)
source_group(Engine\\Graphics FILES ${SRC_ENGINE_GRAPHICS})

# Input Components
set(SRC_ENGINE_INPUT 
	"src/engine/input/InputManager.hpp"
	"src/engine/input/InputManager.cpp"
	"src/engine/input/KeyboardListener.hpp"
	"src/engine/input/MouseListener.hpp"
	"src/engine/input/GamepadListener.hpp"
)
source_group(Engine\\Input FILES ${SRC_ENGINE_INPUT})

# Common Components
set(SRC_ENGINE_COMMON_PATTERNS 
	"src/engine/common/patterns/Singleton.hpp"
	"src/engine/common/patterns/Singleton.inl"
)
source_group(Engine\\Common\\Patterns FILES ${SRC_ENGINE_COMMON_PATTERNS})

set(SRC_ENGINE_COMMON ${SRC_ENGINE_COMMON_PATTERNS})

set(SRC_ENGINE_ALL 
	${SRC_ENGINE_GAME}
	${SRC_ENGINE_DEBUGGING}
	${SRC_ENGINE_GRAPHICS}
	${SRC_ENGINE_INPUT}
	${SRC_ENGINE_COMMON}
)

add_library(Engine ${SRC_ENGINE_ALL})
target_link_libraries(TwoSoulsTale Engine)



################################################################
# Game library                                                 #
################################################################