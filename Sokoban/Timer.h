#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer();
	~Timer() = default;

	void Start();
	void Stop();
	float GetElapsedMS();

	void Reset();

private:
	Uint64 m_start, m_end;
	Uint64 m_frequency;
};
