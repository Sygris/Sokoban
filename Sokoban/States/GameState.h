#pragma once

#include <SDL.h>
#include "../Application.h"

class GameState
{
public:
	virtual void Init(Application* application) = 0;
	virtual void Clean() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void ChangeState(Application* application, GameState* state)
	{
		application->ChangeState(state);
	}

protected:
	GameState() {};

	Application* m_application{ nullptr };
};

