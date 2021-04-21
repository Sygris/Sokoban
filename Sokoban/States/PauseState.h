#pragma once
#include "GameState.h"
class PauseState : public GameState
{
public:
	void Init(Application* application);
	void Clean();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

	static PauseState* Instance() { return &s_pauseState; }

protected:
	PauseState();
private:
	static PauseState s_pauseState;

	SDL_Texture* m_text{ nullptr };
};

