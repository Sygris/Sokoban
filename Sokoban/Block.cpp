#include "Block.h"

#include "Map.h"
#include "Timer.h"
#include "CollisionHandler.h"
#include "TextureManager.h"

std::vector<Block*> Block::BlockList;

Block::Block(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size, const std::string& colour, Map* map)
	: GameObject(renderer, filename, position, size), m_colour{ colour }, m_map{ map }
{
	BlockList.push_back(this);
}

std::string Block::GetColour()
{
	return m_colour;
}

void Block::Move(int x, int y)
{
	if (x > 0)
	{
		Right(x);
	}
	else if (x < 0)
	{
		Left(x);
	}
	else if (y > 0)
	{
		Down(y);
	}
	if (y < 0)
	{
		Up(y);
	}
}

void Block::Update()
{
	m_dstRect.x = (int)m_position.x;
	m_dstRect.y = (int)m_position.y;
}

void Block::Draw()
{
	TextureManager::Draw(m_texture, m_renderer, m_srcRect, m_dstRect);
}

void Block::SnapToExit(Vector2D position)
{
	m_position = position;
	m_dstRect.x = (int)m_position.x;
	m_dstRect.y = (int)m_position.y;
}

void Block::Up(float velocity)
{
	bool canMove = false;
	int y = m_position.y + velocity * Timer::GetInstance()->GetDeltaTime();

	SDL_Rect temp = { m_position.x, y, m_size.x, m_size.y };

	if (!m_map->IsWall(m_position.x, y) && !m_map->IsWall(m_position.x + (m_size.x - 1), y)) // Is not colliidng with wall
	{
		for (Block* block : Block::BlockList) // Check if it is colliding with other blocks
		{
			if (block == this) continue;

			if (CollisionHandler::AABB(block->GetRect(), temp))
			{
				canMove = false;
				break;
			}

			canMove = true;
		}
	}

	if (canMove)
	{
		m_position.y = y;
	}
}

void Block::Right(float velocity)
{
	bool canMove = false;
	int x = m_position.x + velocity * Timer::GetInstance()->GetDeltaTime();

	SDL_Rect temp = { x, m_position.y, m_size.x, m_size.y };

	if (!m_map->IsWall(x + (m_size.x - 1), m_position.y) &&
		!m_map->IsWall(x + (m_size.x - 1), m_position.y + (m_size.y - 1))) // Is not colliidng with wall
	{
		for (Block* block : Block::BlockList) // Is not colliding with other blocks
		{
			if (block == this) continue;

			if (CollisionHandler::AABB(block->GetRect(), temp))
			{
				canMove = false;
				break;
			}

			canMove = true;
		}
	}

	if (canMove)
	{
		m_position.x = x;
	}
}

void Block::Down(float velocity)
{
	bool canMove = false;
	int y = m_position.y + velocity * Timer::GetInstance()->GetDeltaTime();

	SDL_Rect temp = { m_position.x, y, m_size.x, m_size.y };

	if (!m_map->IsWall(m_position.x, y + (m_size.y - 1)) &&
		!m_map->IsWall(m_position.x + (m_size.x - 1), y + (m_size.y - 1)))
	{
		for (Block* block : Block::BlockList) // Is not colliding with other blocks
		{
			if (block == this) continue;

			if (CollisionHandler::AABB(block->GetRect(), temp))
			{
				canMove = false;
				break;
			}

			canMove = true;
		}
	}

	if (canMove)
	{
		m_position.y = y;
	}
}

void Block::Left(float velocity)
{
	bool canMove = false;
	int x = m_position.x + velocity * Timer::GetInstance()->GetDeltaTime();

	SDL_Rect temp = { x, m_position.y, m_size.x, m_size.y };

	if (!m_map->IsWall(x, m_position.y) &&
		!m_map->IsWall(x, m_position.y + (m_size.y - 1)))
	{
		for (Block* block : Block::BlockList) // Is not colliding with other blocks
		{
			if (block == this) continue;

			if (CollisionHandler::AABB(block->GetRect(), temp))
			{
				canMove = false;
				break;
			}

			canMove = true;
		}
	}

	if (canMove)
	{
		m_position.x = x;
	}
}
