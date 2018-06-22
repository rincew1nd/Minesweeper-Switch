#pragma once
#include <stdio.h>
#include <vector>
#include <random>
#include <switch.h>
#include <SDL2/SDL.h>
#include "Cell.hpp"

#include "Defaults.hpp"

class Board
{
    public:
        Board(int, int);
        void GenerateBoard();
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