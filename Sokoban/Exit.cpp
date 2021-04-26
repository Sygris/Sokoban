#include "Exit.h"

std::vector<Exit*> Exit::ExitList;

Exit::Exit(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size, const std::string& colour)
	: GameObject(renderer, filename, position, size), m_colour { colour }
{
	ExitList.push_back(this);
}

void Exit::Update()
{
}

void Exit::Draw()
{
}
