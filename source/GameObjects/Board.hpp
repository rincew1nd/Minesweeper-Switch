#pragma once

#include <stdio.h>
#include <vector>
#include <random>
#include <switch.h>
#include <SDL2/SDL.h>

#include "../GameObjects/Cell.hpp"

#include "../Engine/Defaults.hpp"
#include "../Engine/Resources.hpp"

class Board
{
    public:
        Board(int, int, Resources*);
        bool IsAllOpened();
        bool IsOnBoard(int, int);
        void OpenAll();
        void Restart();
        void Draw(SDL_Renderer*);
        void HandleClick(touchPosition*);
        void Move(int, int);

        bool NeedRestart = false;

      private:
        void GenerateBoard();
        Cell* GetCell(int, int);
        
        int GridLeft;
        int GridTop;
        Resources *_resources;
        std::vector<Cell*> _cells;
};