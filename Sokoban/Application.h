#pragma once

#if _DEBUG
#include "Util/MemoryManager.h"
#endif // DEBUG

#include <vector>
#include "Renderer.h"

class GameState;
class Audio;
class Input;
class Text;

class Application
{
public:
	Application();
	~Application();

	void ChangeState(GameState* state);
	void RestartState(GameState* state);
	void GoToMenuState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void Run();
	void Destroy();

	void ChangeFPS();

	inline Input* GetInput() { return m_input; }
	inline Audio* GetAudio() { return m_sounds; }
	inline SDL_Renderer* GetRenderer() { return m_renderer->GetRenderer(); }

	void Quit() { m_isRunning = false; }

private:
	Renderer* m_renderer{ nullptr };
	bool m_isRunning{ false };

	std::vector<GameState*> m_states;

	Input* m_input;
	Audio* m_sounds;

#pragma region Timer
	float m_fps{ SIXTY };

	Text* m_textFPS{ nullptr };

	int m_currentFPS = 0; // Keeps the current fps selection (toggle fps)
	enum FPS {THIRTY = 30, SIXTY = 60, HUNDREDTWENTY = 120, TotalOfFPS = 3};
#pragma endregion
};

