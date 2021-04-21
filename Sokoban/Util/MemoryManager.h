#pragma once

#include <iostream>
#include <string>

#include "Logger.h"

static size_t totalHeapMemory = 0;

#pragma region Operator new overload
inline void* operator new(size_t size, const char* filename, int line)
{
	totalHeapMemory += size;

	void* ptr = new char[size];

	std::string debug = "Size: " + std::to_string(size) + " bytes." + " Filename: " + filename + " line: " + std::to_string(line);

	Logger::GetLogger()->Log(debug);

	return ptr;
}

inline void* operator new[](size_t size, const char* filename, int line)
{
	totalHeapMemory += size;

	void* ptr = new char[size];

	std::string debug = "Size: " + std::to_string(size) + " bytes." + " Filename: " + filename + " line: " + std::to_string(line);

	Logger::GetLogger()->Log(debug);

	return ptr;
}
#pragma endregion

#pragma region Operator delete overload
// Exception delete: parameters match the overloaded new and will be used
// if the object creation throws an exception
inline void operator delete(void* ptr, const char* filename, int line)
{
	free(ptr);
}

// If successfull object creation, the following deletes will be used
inline void operator delete(void* ptr)
{
	free(ptr);
}

inline void operator delete[](void* ptr)
{
	free(ptr);
}
#pragma endregion

// Exploit the preprocessor
#define new new(__FILE__,__LINE__)