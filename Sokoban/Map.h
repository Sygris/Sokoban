#pragma once

#include <SDL.h>
#include <vector>
#include "vector2D.h"
#include <String>

class Scroll;

class Map
{
public:
	Map(SDL_Renderer* renderer, const char* mapFilePath, const char* tilesetPath, int blockSize, float scaleSize = 1);
	~Map();

	void LoadMap(std::string path);

	void Render();

	bool IsWall(int x, int y);

	inline std::vector<Vector2D> GetPlayersPositions() { return m_playerStartPosition; }

private:
	void CreateBlocks();
	void CreatePlayerStarPositions();
	void CreateHome();
private:
	SDL_Rect m_srcRect{}, m_destRect{}, m_mapSize{};

	SDL_Texture* m_tileset;
	SDL_Renderer* m_renderer{ nullptr };

	int m_blocksize;			// Size of the tile
	float m_scaleBlocksize;		// Scalar for the size

	int m_width, m_height;

	std::vector<std::string> m_mapLayout;
	std::vector<Vector2D> m_playerStartPosition;
};
