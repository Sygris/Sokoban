#pragma once

#include <chrono>

class Timer
{
public:

	inline float GetDeltaTime() { return m_deltaTime; }

	inline float GetCurrentFPS() { return m_currentFPS; }

	inline double GetElapsedTime() { return m_elapsedTime; }

	void Tick();

	void CalculateFPS();

	static Timer* GetInstance();

private:
	Timer() = default;

	static Timer* s_instance;

	float m_deltaTime;
	float m_currentFPS;
	double m_elapsedTime;

	std::chrono::time_point<std::chrono::high_resolution_clock> m_frameTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_lastFrameTime;
};
