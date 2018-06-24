#pragma once
#include <switch.h>
#include <SDL2/SDL.h>

#include "Defaults.hpp"
#include "Input.hpp"
#include "Board.hpp"

class Minesweeper
{
    public:
        Minesweeper();

    private:
        void InitSDL();
        void InitGame();
        void DeinitSDL();
        
        SDL_Window *_window;
        SDL_Renderer *_renderer;

        Input* _input;
        Board* _board;
        Resources* _resources;
};