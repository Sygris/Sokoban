#pragma once

class Timer
{
private:

	static Timer* s_instance;

	unsigned int m_startTicks;
	unsigned int m_elapsedTicks;
	float m_deltaTime;

public:
	static Timer* Instance();
	static void Destroy();

	void Reset();
	float DeltaTime();

	void Update();

private:

	Timer();
	~Timer();
};
