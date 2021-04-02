#pragma once

#if _DEBUG
#include "Util/MemoryManager.h"
#endif // DEBUG

#include <vector>
#include "Renderer.h"
#include "Timer.h"

class GameState;
class Audio;

class Application
{
public:
	Application();
	~Application();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void Run();
	void Destroy();

	void ChangeFPS(float fps);

	void Quit() { m_isRunning = false; }

	Renderer* GetRenderer() { return m_renderer; }
	Audio* m_sounds;

private:
	Renderer* m_renderer{ nullptr };
	bool m_isRunning{ false };

	std::vector<GameState*> m_states;

#pragma region Timer
	Timer* m_timer{ nullptr };
	float m_fps{ 60.0f };

	// TODO: Be able to change between 30, 60 and 120 FPS
#pragma endregion

};

