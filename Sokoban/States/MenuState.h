#pragma once

#include "GameState.h"

class Button;

class MenuState : public GameState
{
public:
	void Init(Renderer* renderer, Input* input, Audio* audio);
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

	Button* m_button;
};

