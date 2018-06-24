#pragma once
#include <switch.h>
#include <SDL2/SDL.h>

#include "Defaults.hpp"
#include <map>
#include <vector>
#include <utility>

class Resources
{
    public:
        Resources() {};
        void LoadROMFS(SDL_Renderer*);
        SDL_Texture* GetTexture(CellState, int);
    private:
        std::vector<SDL_Surface*> _surfaces;
        std::map<CellState, std::vector<SDL_Texture*>> _textures;
};