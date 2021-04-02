#include "Timer.h"

Timer::Timer()
{
	Reset();
	m_frequency = SDL_GetPerformanceFrequency();
}

void Timer::Start()
{
	m_start = SDL_GetPerformanceCounter();
}

void Timer::Stop()
{
	m_end = SDL_GetPerformanceCounter();
}

float Timer::GetElapsedMS()
{
	float elapsed = (float)(m_end - m_start) / (double)m_frequency;
	elapsed *= 1000;
	return elapsed;
}

void Timer::Reset()
{
	m_start = 0.0f;
	m_end = 0.0f;
}
