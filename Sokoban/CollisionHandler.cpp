#include "CollisionHandler.h"
#include <SDL.h>

bool CollisionHandler::AABB(SDL_Rect a, SDL_Rect b)
{
	if (a.x < b.x + (b.w - 1) &&
		a.x + (a.w - 1) > b.x &&
		a.y < b.y + (b.h - 1) &&
		a.y + (a.h - 1) > b.y)
	{
		return true;
	}

    return false;
}
