#pragma once
#include <stdio.h>
#include <vector>
#include <random>
#include <switch.h>
#include <SDL2/SDL.h>
#include "Cell.hpp"

#include "Defaults.hpp"
#include "Resources.hpp"

class Board
{
    public:
        Board(int, int, Resources*);
        void GenerateBoard(Resources*);
        Cell* GetCell(int, int);
        bool IsAllOpened();
        bool IsOnBoard(int, int);
        void OpenAll();
        void Restart();
        
        void Draw(SDL_Renderer*);
        void HandleClick(touchPosition*);
    private:
        std::vector<Cell*> _cells;
        int GridLeft;
        int GridTop;
};