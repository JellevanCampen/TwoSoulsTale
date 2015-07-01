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
set(CMAKE_DLLS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dll") # (Not an official CMake variable)

# Switch to the x86 or x64 versions of the DLL and LIB folders
IF(CMAKE_EXE_LINKER_FLAGS MATCHES "x64")
	message(STATUS "Using x64 versions of DLLs and libraries")
	set (CMAKE_DLLS_PATH ${CMAKE_DLLS_PATH}/x64)
	set (CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}/x64)
ELSE()
	message(STATUS "Using x86 versions of DLLs and libraries")
	set (CMAKE_DLLS_PATH ${CMAKE_DLLS_PATH}/x86)
	set (CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}/x86)
ENDIF()

# Add the main executable
add_executable(TwoSoulsTale src/main.cpp)

# Copy DLLs to the build directory
add_custom_command(TARGET TwoSoulsTale POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_DLLS_PATH}" $<TARGET_FILE_DIR:TwoSoulsTale>
)



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
	add_definitions(${GLFW_DEFINITIONS})
endif (GLFW_FOUND)

# GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${GLEW_LIBRARIES})
	add_definitions(${GLEW_DEFINITIONS})
endif (GLEW_FOUND)

# irrKlang
find_package(irrKlang REQUIRED)
if (IRRKLANG_FOUND)
	include_directories(${IRRKLANG_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${IRRKLANG_LIBRARIES})
	add_definitions(${IRRKLANG_DEFINITIONS})
endif (IRRKLANG_FOUND)

# FreeImage
find_package(FreeImage REQUIRED)
if (FREEIMAGE_FOUND)
	include_directories(${FREEIMAGE_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${FREEIMAGE_LIBRARIES})
	add_definitions(${FREEIMAGE_DEFINITIONS})
endif (FREEIMAGE_FOUND)

# GLM
find_package(GLM REQUIRED)
if (GLM_FOUND)
	include_directories(${GLM_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${GLM_LIBRARIES})
	add_definitions(${GLM_DEFINITIONS})
endif (GLM_FOUND)

# Box2D
find_package(BOX2D REQUIRED)
if (BOX2D_FOUND)
	include_directories(${BOX2D_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${BOX2D_LIBRARIES})
	add_definitions(${BOX2D_DEFINITIONS})
endif (BOX2D_FOUND)

# TinyXML2
find_package(TINYXML2 REQUIRED)
if (TINYXML2_FOUND)
	include_directories(${TINYXML2_INCLUDE_DIRS})
	target_link_libraries(TwoSoulsTale ${TINYXML2_LIBRARIES})
	add_definitions(${TINYXML2_DEFINITIONS})
endif (TINYXML2_FOUND)



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

# Audio Components
set(SRC_ENGINE_AUDIO 
	"src/engine/audio/AudioManager.hpp"
	"src/engine/audio/AudioManager.cpp"
	"src/engine/audio/AudioResource.hpp"
	"src/engine/audio/AudioResource.cpp"
)
source_group(Engine\\Audio FILES ${SRC_ENGINE_AUDIO})

# Graphics Components
set(SRC_ENGINE_GRAPHICS 
	"src/engine/graphics/GraphicsManager.hpp"
	"src/engine/graphics/GraphicsManager.cpp"
	"src/engine/graphics/SpriteSheetResource.hpp"
	"src/engine/graphics/SpriteSheetResource.cpp"
	
)
source_group(Engine\\Graphics FILES ${SRC_ENGINE_GRAPHICS})

# Resources Components
set(SRC_ENGINE_RESOURCES
	"src/engine/resources/Resource.hpp"
	"src/engine/resources/Resource.cpp"
	"src/engine/resources/ResourceManager.hpp"
	"src/engine/resources/ResourceManager.cpp"
)
source_group(Engine\\Resources FILES ${SRC_ENGINE_RESOURCES})

# Input Components
set(SRC_ENGINE_INPUT 
	"src/engine/input/InputManager.hpp"
	"src/engine/input/InputManager.cpp"
	"src/engine/input/KeyboardListener.hpp"
	"src/engine/input/MouseListener.hpp"
	"src/engine/input/GamepadListener.hpp"
)
source_group(Engine\\Input FILES ${SRC_ENGINE_INPUT})

# Timing Components
set(SRC_ENGINE_TIMING
	"src/engine/timing/TimingManager.hpp"
	"src/engine/timing/TimingManager.cpp"
	"src/engine/timing/AlarmListener.hpp"
)
source_group(Engine\\Timing FILES ${SRC_ENGINE_TIMING})

# World Components
set(SRC_ENGINE_WORLD 
	"src/engine/world/WorldManager.hpp"
	"src/engine/world/WorldManager.cpp"
	"src/engine/world/CollisionManager.hpp"
	"src/engine/world/CollisionManager.cpp"
	"src/engine/world/GameObject.hpp"
	"src/engine/world/GameObject.cpp"
)
source_group(Engine\\World FILES ${SRC_ENGINE_WORLD})

# Common Components
set(SRC_ENGINE_COMMON_UTILITY 
	"src/engine/common/utility/ImageReader.hpp"
	"src/engine/common/utility/ImageReader.cpp"
	# "src/engine/common/utility/BinaryFileIO.hpp"
	# "src/engine/common/utility/BinaryFileIO.cpp"
	"src/engine/common/utility/XMLFileIO.hpp"
	"src/engine/common/utility/XMLFileIO.cpp"
	"src/engine/common/utility/ParameterFileIO.hpp"
	"src/engine/common/utility/ParameterFileIO.cpp"
	"src/engine/common/utility/PathConfig.hpp"
	"src/engine/common/utility/PathConfig.cpp"
	"src/engine/common/utility/GameTime.hpp"
	"src/engine/common/utility/VectorTypes.hpp"
	"src/engine/common/utility/MatrixTypes.hpp"
	"src/engine/common/utility/IntervalTypes.hpp"
	"src/engine/common/utility/TransformTypes.hpp"
)
source_group(Engine\\Common\\Utility FILES ${SRC_ENGINE_COMMON_UTILITY})

set(SRC_ENGINE_COMMON_PATTERNS 
	"src/engine/common/patterns/Singleton.hpp"
	"src/engine/common/patterns/Singleton.inl"
)
source_group(Engine\\Common\\Patterns FILES ${SRC_ENGINE_COMMON_PATTERNS})

set(SRC_ENGINE_COMMON ${SRC_ENGINE_COMMON_UTILITY} ${SRC_ENGINE_COMMON_PATTERNS})

set(SRC_ENGINE_ALL 
	${SRC_ENGINE_GAME}
	${SRC_ENGINE_DEBUGGING}
	${SRC_ENGINE_AUDIO}
	${SRC_ENGINE_GRAPHICS}
	${SRC_ENGINE_RESOURCES}
	${SRC_ENGINE_INPUT}
	${SRC_ENGINE_TIMING}
	${SRC_ENGINE_WORLD}
	${SRC_ENGINE_COMMON}
)

add_library(Engine ${SRC_ENGINE_ALL})
target_link_libraries(TwoSoulsTale Engine)



################################################################
# Game library                                                 #
################################################################

# Test components
set(SRC_GAME_TEST 
	"src/game/test/TestObject.hpp"
	"src/game/test/TestObject.cpp"
	"src/game/test/TestObject2.hpp"
	"src/game/test/TestObject2.cpp"
)
source_group(Game\\Test FILES ${SRC_GAME_TEST})

# Identifiers
set(SRC_GAME_IDENTIFIERS
	"src/game/identifiers/GameObjectTypeIdentifiers.hpp"
)
source_group(Game\\Identifiers FILES ${SRC_GAME_IDENTIFIERS})

set(SRC_GAME_ALL 
	${SRC_GAME_TEST}
	${SRC_GAME_IDENTIFIERS}
)

add_library(Game ${SRC_GAME_ALL})
target_link_libraries(TwoSoulsTale Game)