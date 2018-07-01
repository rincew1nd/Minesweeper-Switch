#include "Resources.hpp"

void Resources::LoadROMFS(SDL_Renderer* renderer)
{
    //Cell textures
    std::vector<SDL_Texture*> closedVector;
    closedVector.push_back(LoadTexture(renderer, "closed"));
    _cellTextures.insert(std::make_pair(Closed, closedVector));
    
    std::vector<SDL_Texture*> openedVector;
    for (int i = 0; i < 10; i++)
        openedVector.push_back(LoadTexture(renderer, "cell" + std::to_string(i)));
    _cellTextures.insert(std::make_pair(Opened, openedVector));

    std::vector<SDL_Texture*> flaggedVector;
    flaggedVector.push_back(LoadTexture(renderer, "flagged"));
    _cellTextures.insert(std::make_pair(Flagged, flaggedVector));

    //Button textures
    _textures.insert(std::make_pair("flagOnButton", LoadTexture(renderer, "flagOnButton")));
    _textures.insert(std::make_pair("flagOffButton", LoadTexture(renderer, "flagOffButton")));
    _textures.insert(std::make_pair("restartButton", LoadTexture(renderer, "restartButton")));
    _textures.insert(std::make_pair("settingsButton", LoadTexture(renderer, "settingsButton")));
    _textures.insert(std::make_pair("escButton", LoadTexture(renderer, "escButton")));
    _textures.insert(std::make_pair("arrowRightButton", LoadTexture(renderer, "arrowRightButton")));
    _textures.insert(std::make_pair("arrowLeftButton", LoadTexture(renderer, "arrowLeftButton")));
    _textures.insert(std::make_pair("minusButton", LoadTexture(renderer, "minusButton")));
    _textures.insert(std::make_pair("plusButton", LoadTexture(renderer, "plusButton")));

    //Font
    _font = TTF_OpenFont("romfs:/Pixeled.ttf", 28);
}

SDL_Texture* Resources::LoadTexture(SDL_Renderer* renderer, std::string image)
{
    char imagePath[50];
    sprintf(imagePath, "romfs:/%s.bmp", image.c_str());

    SDL_Surface* surface = SDL_LoadBMP(imagePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* Resources::GetTexture(CellState state, int order)
{
    return _cellTextures[state].at(order);
}

SDL_Texture *Resources::GetTexture(std::string textureName)
{
    return _textures[textureName];
}

TTF_Font* Resources::GetFont()
{
    return _font;
}

Resources::~Resources()
{
    //for (int i = 0; i < )
}