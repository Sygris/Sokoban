#pragma once

#include <SDL.h>

#include "GameState.h"

class MenuState : public GameState
{
public:
	void Init();
	void Clean();

	void Pause();
	void Resume();

	void HandleEvents(Application* application);
	void Update(Application* application);
	void Draw(Application* application);

	static MenuState* Instance() { return &s_menuState; }
protected:
	MenuState();
private:
	static MenuState s_menuState;
};

