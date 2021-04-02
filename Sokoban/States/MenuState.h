#pragma once

#include "GameState.h"

class Input;

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

	Input* m_input{ nullptr };
private:
	static MenuState s_menuState;

	SDL_Texture* m_texture{nullptr};
};

