#pragma once

class SDL_Rect;

class CollisionHandler
{
public:
	static bool AABB(SDL_Rect a, SDL_Rect b);
};

