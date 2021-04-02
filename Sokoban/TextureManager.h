#pragma once

#include <SDL.h>
#include <string>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const std::string& filename, SDL_Renderer* renderer);
	static void Draw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest);
};

