#include "Exit.h"
#include "TextureManager.h"
#include "Block.h"
#include "CollisionHandler.h"

std::vector<Exit*> Exit::ExitList;

Exit::Exit(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size, const std::string& colour)
	: GameObject(renderer, filename, position, size), m_colour { colour }
{
	ExitList.push_back(this);
}

void Exit::Update()
{
	for (Block* block : Block::BlockList)
	{
		if (block->GetColour() == m_colour)
		{
			if (CollisionHandler::AABB(block->GetRect(), m_dstRect))
			{
				block->SnapToExit(m_position);
				block->IsHome(true);

				RemoveFromList();
			}
		}
	}
}

void Exit::Draw()
{
	TextureManager::Draw(m_texture, m_renderer, m_srcRect, m_dstRect);
}

void Exit::RemoveFromList()
{
	for (size_t i = 0; i < ExitList.size(); i++)
	{
		if (ExitList[i] == this)
		{
			ExitList.erase(ExitList.begin() + i);
			delete this;
		}
	}
}
