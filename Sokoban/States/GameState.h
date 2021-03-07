#pragma once

#include "../Application.h"

class GameState
{
public:
	virtual void Init() = 0;
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
};

