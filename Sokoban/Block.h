#pragma once

#include "GameObject.h"

class Map;

class Block : GameObject
{
public:
	Block(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size, const std::string& color, Map* map);

	std::string GetColour();

	void Move(int x, int y);

	void Update();
	void Draw();

	inline Vector2D GetPosition() { return m_position; }
	void SnapToExit(Vector2D position);

	inline SDL_Rect GetRect() { return m_dstRect; }

	inline bool IsHome() { return m_isHome; }
	inline void IsHome(bool ishome) { m_isHome = ishome; }

	static std::vector<Block*> BlockList;

private:
	std::string m_colour;

	bool m_isHome = false;

	Map* m_map{ nullptr };

	void Up(float velocity);
	void Right(float velocity);
	void Down(float velocity);
	void Left(float velocity);
};

