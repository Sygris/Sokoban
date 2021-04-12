#pragma once

#include "GameState.h"

class Button;

enum MainMenuButtons { PLAY, OPTIONS, EXIT, TOTAL };

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

	SDL_Texture* m_background{ nullptr };

	int m_currentButton = 0;
	std::vector<Button*> m_buttons;

	void ChangeSelection(int change);
};

