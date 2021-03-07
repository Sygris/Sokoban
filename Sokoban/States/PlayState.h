#pragma once
#include "GameState.h"
class PlayState : public GameState
{
public:
	void Init();
	void Clean();

	void Pause();
	void Resume();

	void HandleEvents(Application* application);
	void Update(Application* application);
	void Draw(Application* application);

	static PlayState* Instance() { return &s_playState; }

protected:
	PlayState();
private:
	static PlayState s_playState;
};

