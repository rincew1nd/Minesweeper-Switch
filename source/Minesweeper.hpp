#pragma once
#include <switch.h>
#include <SDL2/SDL.h>

#include "Input.hpp"
#include "Button.hpp"

class Minesweeper
{
    public:
        Minesweeper();

    private:
        void InitSDL();
        void DeinitSDL();
        
        SDL_Window *window;
        SDL_Renderer *renderer;
        Input *input;
};