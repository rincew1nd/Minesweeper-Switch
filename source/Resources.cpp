#include "Resources.hpp"

void Resources::LoadROMFS(SDL_Renderer* renderer)
{
    //Cell textures
    std::vector<SDL_Texture*> closedVector;
    SDL_Surface* surface = SDL_LoadBMP("romfs:/closed.bmp");
    closedVector.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    _surfaces.push_back(surface);
    _cellTextures.insert(std::make_pair(Closed, closedVector));
    
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
    _cellTextures.insert(std::make_pair(Opened, openedVector));

    std::vector<SDL_Texture*> flaggedVector;
    surface = SDL_LoadBMP("romfs:/flagged.bmp");
    flaggedVector.push_back(SDL_CreateTextureFromSurface(renderer, surface));
    _surfaces.push_back(surface);
    _cellTextures.insert(std::make_pair(Flagged, flaggedVector));

    //Button textures
    surface = SDL_LoadBMP("romfs:/flagOnButton.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    _surfaces.push_back(surface);
    _textures.insert(std::make_pair("flagOnButton", texture));

    surface = SDL_LoadBMP("romfs:/flagOffButton.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    _surfaces.push_back(surface);
    _textures.insert(std::make_pair("flagOffButton", texture));

    surface = SDL_LoadBMP("romfs:/restart.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    _surfaces.push_back(surface);
    _textures.insert(std::make_pair("flagOffButton", texture));
}

SDL_Texture* Resources::GetTexture(CellState state, int order)
{
    return _cellTextures[state].at(order);
}

SDL_Texture *Resources::GetTexture(std::string textureName)
{
    return _textures[textureName];
}