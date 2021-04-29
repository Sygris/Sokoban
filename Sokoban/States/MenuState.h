#pragma once

#include "GameState.h"

class Button;

enum MainMenuButtons { PLAY, MULTIPLAYER, EXIT, TOTAL };

class MenuState : public GameState
{
public:
	void Init(Application* application);
	void Clean();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

	static MenuState* Instance() { return &s_menuState; }

protected:
	MenuState();

private:
	static MenuState s_menuState;

	SDL_Texture* m_background{ nullptr };

	int m_currentButton = 0;
	std::vector<Button*> m_buttons;

	void ChangeSelection(int change);
};

