#pragma once

#include "GameObject.h"

class Map;

class Block : GameObject
{
public:
	Block(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size, Vector2D home, Map* map);
	
	bool IsBlockHome();

	void Move(int x, int y);

	void Update();
	void Draw();

	inline Vector2D GetPosition() { return m_position; }

	static std::vector<Block*> BlockList;

private:
	bool m_isHome{ false };
	Vector2D m_home;

	Map* m_map{ nullptr };

	void Up(float velocity);
	void Right(float velocity);
	void Down(float velocity);
	void Left(float velocity);
};

