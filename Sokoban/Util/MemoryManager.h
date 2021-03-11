#pragma once
#include <iostream>

static size_t totalHeapMemory = 0;

#pragma region Operator new overload
inline void* operator new(size_t size, const char* filename, int line)
{
	totalHeapMemory += size;

	void* ptr = new char[size];

	std::cout << "Size: " << size << " bytes." << " Filename: " << filename << " line: " << line << std::endl;
	std::cout << "Total heap allocation = " << totalHeapMemory << " bytes" << std::endl;

	return ptr;
}

inline void* operator new[](size_t size, const char* filename, int line)
{
	totalHeapMemory += size;

	void* ptr = new char[size];

	std::cout << "Size: " << size << " bytes." << " Filename: " << filename << " line: " << line << std::endl;
	std::cout << "Total heap allocation = " << totalHeapMemory << " bytes" << std::endl;

	return ptr;
}
#pragma endregion

#pragma region Operator delete overload
// Exception delete: parameters match the overloaded new and will be used
// if the object creation throws an exception
inline void operator delete(void* ptr, const char* filename, int line)
{
	//totalHeapMemory -= _msize(ptr);

	//std::cout << _msize(ptr) << " bytes released" << std::endl;
	//std::cout << "Total heap allocation = " << totalHeapMemory << " bytes " << std::endl;

	free(ptr);
}

// If successfull object creation, the following deletes will be used
inline void operator delete(void* ptr)
{
	//totalHeapMemory -= _msize(ptr);

	//std::cout << _msize(ptr) << " bytes released" << std::endl;
	//std::cout << "Total heap allocation = " << totalHeapMemory << " bytes " << std::endl;

	free(ptr);
}

inline void operator delete[](void* ptr)
{
	//totalHeapMemory -= _msize(ptr);

	//std::cout << _msize(ptr) << " bytes released" << std::endl;
	//std::cout << "Total heap allocation = " << totalHeapMemory << " bytes " << std::endl;

	free(ptr);
}
#pragma endregion

// Exploit the preprocessor
#define new new(__FILE__,__LINE__)