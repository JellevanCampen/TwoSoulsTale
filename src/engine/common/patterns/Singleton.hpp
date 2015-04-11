#pragma once
#ifndef ENGINE_COMMON_PATTERNS_SINGLETON_H
#define ENGINE_COMMON_PATTERNS_SINGLETON_H

template<typename T>
class Singleton
{
public:
	static T& GetInstance();
	static const T* const Create();	
	static void Destroy();

private:
	static T* m_Instance;

};

#include "Singleton.inl"

#endif
