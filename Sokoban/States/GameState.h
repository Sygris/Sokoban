#pragma once

#include <SDL.h>
#include "../Application.h"

class GameState
{
public:
	virtual void Init(Renderer* renderer, Input* input, Audio* audio) = 0;
	virtual void Clean() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(Application* application) = 0;
	virtual void Update(Application* application) = 0;
	virtual void Draw(Application* application) = 0;

	void ChangeState(Application* application, GameState* state)
	{
		application->ChangeState(state);
	}

protected:
	GameState() {};

	Input* m_input{ nullptr };
	Audio* m_sounds{ nullptr };
	Renderer* m_renderer{ nullptr };
};

