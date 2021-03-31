#pragma once

#if _DEBUG
#include "Util/MemoryManager.h"
#endif // DEBUG

#include "Renderer.h";

#include <vector>

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

	void Quit() { m_isRunning = false; }

	Renderer* GetRenderer() { return m_renderer; }
	Audio* m_sounds;

private:
	Renderer* m_renderer{ nullptr };
	bool m_isRunning{ false };

	std::vector<GameState*> m_states;

};

