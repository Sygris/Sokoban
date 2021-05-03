#pragma once
#include "GameState.h"
#include "../Util/MessageHandler.h"
#include <string>

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

	void Replay(Application* application) override;
	void Setup(std::string file);

	static PlayState* Instance() { return &s_playState; }

protected:
	PlayState();
private:
	static PlayState s_playState;

	Map* m_map{ nullptr };
	std::string m_currentMapFilePath;

	void CreatePlayers();
	std::vector<Player*> m_players;

	MessageHandler* messageHandler{nullptr};
};

