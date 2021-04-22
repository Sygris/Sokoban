#include "Timer.h"
#include <SDL.h>

Timer* Timer::s_instance = nullptr;

Timer* Timer::Instance()
{
	if (nullptr == s_instance)
		s_instance = new Timer();

	return s_instance;
}

void Timer::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

Timer::Timer()
{
	Reset();
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	m_startTicks = SDL_GetTicks();
	m_elapsedTicks = 0;
	m_deltaTime = 0.0f;
}

float Timer::DeltaTime()
{
	return m_deltaTime;
}

void Timer::Update()
{
	m_elapsedTicks = SDL_GetTicks() - m_startTicks;

	m_deltaTime = m_elapsedTicks * 0.001f;
}