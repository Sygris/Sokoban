#pragma once
#include "GameState.h"
class PauseState : public GameState
{
public:
	void Init(Renderer* renderer, Input* input, Audio* audio);
	void Clean();

	void Pause();
	void Resume();

	void HandleEvents(Application* application);
	void Update(Application* application);
	void Draw(Application* application);

	static PauseState* Instance() { return &s_pauseState; }

protected:
	PauseState();
private:
	static PauseState s_pauseState;
};

