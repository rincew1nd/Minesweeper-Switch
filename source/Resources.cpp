#include "Resources.hpp"

void Resources::LoadROMFS(SDL_Renderer* renderer)
{
    std::vector<SDL_Texture*> closedVector;
    SDL_Surface* surface = SDL_LoadBMP("romfs:/closed.bmp");
    closedVector.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    _surfaces.push_back(surface);
    _textures.insert(std::make_pair(Closed, closedVector));
    
    std::vector<SDL_Texture*> openedVector;
    for (int i = 0; i < 10; i++)
    {
        char numstr[18];
        sprintf(numstr, "romfs:/cell%01d.bmp", i);
        printf("Load %s\n", numstr);
        SDL_Surface* surface1 = SDL_LoadBMP(numstr);
        openedVector.push_back(SDL_CreateTextureFromSurface(renderer, surface1));
        _surfaces.push_back(surface1);
    }
    _textures.insert(std::make_pair(Opened, openedVector));

    std::vector<SDL_Texture*> flaggedVector;
    SDL_Surface* surface2 = SDL_LoadBMP("romfs:/flagged.bmp");
    flaggedVector.push_back(SDL_CreateTextureFromSurface(renderer, surface2));
    _surfaces.push_back(surface2);
    _textures.insert(std::make_pair(Flagged, flaggedVector));
}

SDL_Texture* Resources::GetTexture(CellState state, int order)
{
    return _textures[state].at(order);
}