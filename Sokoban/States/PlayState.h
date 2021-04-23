#pragma once
#include "GameState.h"

class Map;
class Player;

class PlayState : public GameState
{
public:
	void Init(Application* application);
	void Clean();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

	static PlayState* Instance() { return &s_playState; }

protected:
	PlayState();
private:
	static PlayState s_playState;

	Map* m_map{ nullptr };
	Player* m_player{ nullptr };
};

