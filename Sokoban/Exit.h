#pragma once
#include "GameObject.h"

class Exit : public GameObject
{
public:
	Exit(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size, const std::string& colour);

	void Update();
	void Draw();

	static std::vector<Exit*> ExitList;

private:
	std::string m_colour;

	void RemoveFromList();
};

