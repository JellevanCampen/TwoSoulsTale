#pragma once
#ifndef ENGINE_COMMON_UTILITY_GAMETIME_H
#define ENGINE_COMMON_UTILITY_GAMETIME_H

namespace Engine{

	// Structure for storing timing information
	struct GameTime
	{
		unsigned int deltaTimeMicros;
		unsigned long long totalTimeMicros;
		unsigned long long frameCount;
	};
}
#endif