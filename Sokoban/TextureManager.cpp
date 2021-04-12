#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const std::string& filename, SDL_Renderer* renderer)
{
    SDL_Surface* tempSurface = IMG_Load(filename.c_str());

    if (tempSurface == nullptr)
    {
        std::cout << SDL_GetError() << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

    SDL_FreeSurface(tempSurface);

    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(renderer, texture, &src, &dest);
}
