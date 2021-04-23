#include "Timer.h"
#include <iostream>

Timer* Timer::s_instance = nullptr;

void Timer::Tick()
{
	m_frameTime = std::chrono::steady_clock::now();

	m_deltaTime = std::chrono::duration<float, std::milli>(m_frameTime - m_lastFrameTime).count();
	m_deltaTime /= 1000;
}

void Timer::CalculateFPS()
{
	m_lastFrameTime = m_frameTime;

	m_currentFPS++;
	m_elapsedTime += m_deltaTime;

	if (m_elapsedTime >= 1) // If a second has pass the game will print how many FPS had passed
	{
		m_elapsedTime = 0;
		m_lastFPS = m_currentFPS;
		m_currentFPS = 0;
	}
}

Timer* Timer::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Timer();
	}

	return s_instance;
}
