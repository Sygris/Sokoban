#include "Map.h"
#include "TextureManager.h"
#include "Block.h"
#include <fstream>
#include "Exit.h"

Map::Map(SDL_Renderer* renderer, const char* mapFilePath, const char* tilesetPath, int blockSize, float scaleSize)
	: m_renderer{ renderer }, m_blocksize{ blockSize }, m_scaleBlocksize{ scaleSize }
{

	m_tileset = TextureManager::LoadTexture(tilesetPath, m_renderer);

	m_srcRect.x = m_srcRect.y = 0;
	m_destRect.x = m_destRect.y = 0;

	m_srcRect.w = m_blocksize;
	m_srcRect.h = m_blocksize;

	m_destRect.w = m_blocksize * m_scaleBlocksize;
	m_destRect.h = m_blocksize * m_scaleBlocksize;

	LoadMap(mapFilePath);
}

Map::~Map()
{
	if (m_tileset)
	{
		SDL_DestroyTexture(m_tileset);
		m_tileset = nullptr;
	}

	if (m_renderer)
	{
		m_renderer = nullptr;
	}
}

void Map::LoadMap(std::string path)
{
	std::string line;
	std::ifstream file(path.c_str());

	while (file >> line)
	{
		m_mapLayout.push_back(line);
	}

	file.close();

	CreateBlocks();
	CreateHome();
	CreatePlayerStarPositions();
}

void Map::Render()
{
	char tile;

	for (int row = 0; row < m_mapLayout.size(); row++)
	{
		for (int column = 0; column < m_mapLayout[0].size(); column++)
		{
			tile = m_mapLayout[row][column];

			m_destRect.x = column * m_blocksize * m_scaleBlocksize;
			m_destRect.y = row * m_blocksize * m_scaleBlocksize;

			m_srcRect.x = m_srcRect.w * 11;
			m_srcRect.y = m_srcRect.h * 6;

			TextureManager::Draw(m_tileset, m_renderer, m_srcRect, m_destRect);

			switch (tile)
			{
			case '0':
				m_srcRect.x = m_srcRect.w * 11;
				m_srcRect.y = m_srcRect.h * 6;

				TextureManager::Draw(m_tileset, m_renderer, m_srcRect, m_destRect);
				break;
			case '5':
				m_srcRect.x = m_srcRect.w * 5;
				m_srcRect.y = m_srcRect.h * 0;

				TextureManager::Draw(m_tileset, m_renderer, m_srcRect, m_destRect);
				break;
			default:
				break;
			}
		}
	}
}

bool Map::IsWall(int x, int y)
{
	int size = m_blocksize * m_scaleBlocksize;

	if (m_mapLayout[y / size][x / size] == '5')
		return true;

	return false;
}

void Map::CreateBlocks()
{
	char tile{};

	for (int row = 0; row < m_mapLayout.size(); row++)
	{
		for (int column = 0; column < m_mapLayout[0].size(); column++)
		{
			tile = m_mapLayout[row][column];

			if (tile == '1')
			{
				Block* tmp = new Block(m_renderer,
					"Assets/Blocks/brown.png",
					Vector2D(column * m_blocksize, row * m_blocksize),
					Vector2D(m_blocksize, m_blocksize),
					"brown",
					this
				);
			}
			else if (tile == '3')
			{
				Block* tmp = new Block(m_renderer,
					"Assets/Blocks/blue.png",
					Vector2D(column * m_blocksize, row * m_blocksize),
					Vector2D(m_blocksize, m_blocksize),
					"blue",
					this
				);
			}
		}
	}
}

void Map::CreatePlayerStarPositions()
{
	char tile{};

	for (int row = 0; row < m_mapLayout.size(); row++)
	{
		for (int column = 0; column < m_mapLayout[0].size(); column++)
		{
			tile = m_mapLayout[row][column];

			if (tile == 'P')
			{
				m_playerStartPosition.push_back(Vector2D(column * m_blocksize, row * m_blocksize));
			}
		}
	}
}

void Map::CreateHome()
{
	char tile{};

	for (int row = 0; row < m_mapLayout.size(); row++)
	{
		for (int column = 0; column < m_mapLayout[0].size(); column++)
		{
			tile = m_mapLayout[row][column];

			if (tile == '2')
			{
				Exit* tmp = new Exit(m_renderer,
					"Assets/Exits/brown.png",
					Vector2D(column * m_blocksize, row * m_blocksize),
					Vector2D(m_blocksize, m_blocksize),
					"brown"
				);
			}
			else if (tile == '4')
			{
				Exit* tmp = new Exit(m_renderer,
					"Assets/Exits/blue.png",
					Vector2D(column * m_blocksize, row * m_blocksize),
					Vector2D(m_blocksize, m_blocksize),
					"blue"
				);
			}
		}
	}
}