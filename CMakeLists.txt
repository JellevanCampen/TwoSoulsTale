cmake_minimum_required (VERSION 2.6)

project (TwoSoulsTale)



# Engine Library
set(SRC_ENGINE_GAME 
	"source/engine/Game.hpp"
	"source/engine/Game.cpp"
)
source_group(Engine FILES ${SRC_ENGINE_GAME})

set(SRC_ENGINE_ALL 
	${SRC_ENGINE_GAME}
)

add_library(Engine ${SRC_ENGINE_ALL})

add_executable(TwoSoulsTale source/main.cpp)
target_link_libraries(TwoSoulsTale Engine)