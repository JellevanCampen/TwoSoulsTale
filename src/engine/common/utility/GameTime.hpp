#pragma once
#ifndef ENGINE_COMMON_UTILITY_GAMETIME_H
#define ENGINE_COMMON_UTILITY_GAMETIME_H

namespace Engine{

	// Structure for storing timing information
	struct GameTime
	{
		unsigned int deltaTimeMicros = 0;
		unsigned long long totalTimeMicros = 0;
		unsigned long long frameCount = 0;
	};
}
#endif