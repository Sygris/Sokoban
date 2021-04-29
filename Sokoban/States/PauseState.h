#pragma once

#include "GameState.h"
#include "../UI/Button.h"


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

	inline void IsWonMenu(bool wonMenu) { m_isWonMenu = wonMenu; }
	void Setup(std::string file, bool wonMenu);
	
	static PauseState* Instance() { return &s_pauseState; }
protected:
	PauseState();
private:
	static PauseState s_pauseState;

	SDL_Texture* m_text{ nullptr };

	bool m_isWonMenu{false};

	int m_currentButton = 0;
	std::vector<Button*> m_buttons;

	void ChangeSelection(int change);
	enum PauseMenuButtons { HOME, REPLAY, TOTAL };
};

