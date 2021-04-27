#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const std::string& filename, SDL_Renderer* renderer)
{
    SDL_Surface* tempSurface = IMG_Load(filename.c_str());

#if _DEBUG
    SDL_assert(tempSurface != nullptr);
#endif // _DEBUG


    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

    SDL_FreeSurface(tempSurface);

    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect src, SDL_Rect dest)
{
    // Couldn't pass NULL in the parameters so I had to call SDL_Rect{} and do this check
    // If I had more time I would try by copying the parameter list from SDL_RenderCopy();
    if (src.x == NULL)
    {
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        return;
    }

    SDL_RenderCopy(renderer, texture, &src, &dest);
}