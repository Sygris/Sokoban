#pragma once
#include "GameObject.h"

class Input;
class Audio;
class Map;

enum PlayerStates { IDLE, UP, RIGHT, DOWN, LEFT, TOTAL_PLAYER_STATES };

class Player : public GameObject
{
public:
	Player(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size, Vector2D velocity, Input* input, Audio* audio, Map* map, int playerID);
	~Player();

	void HandleEvents();
	void Update();
	void Draw();

private:
	void Animate(PlayerStates state);
	
	void Up();
	void Down();
	void Right();
	void Left();

private:
	Map* m_map;
	Input* m_input;
	Audio* m_sounds;

	Vector2D m_velocity;

	int m_playerID;

	// Animation Variables
	int m_animationSpeed = 125;

	int m_currentState = IDLE;
	int m_previousState = IDLE;
};

