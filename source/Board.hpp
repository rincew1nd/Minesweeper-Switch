#pragma once
#include <stdio.h>
#include <vector>
#include <random>
#include <switch.h>
#include <SDL2/SDL.h>
#include "Cell.hpp"

#include "Defaults.hpp"
#include "Resources.hpp"
#include "Button.hpp"

class Board
{
    public:
        Board(int, int, Resources*);
        void InitButtons();
        Cell* GetCell(int, int);
        bool IsAllOpened();
        bool IsOnBoard(int, int);
        void OpenAll();
        void Restart();
        void Draw(SDL_Renderer*);
        void HandleClick(touchPosition*);

      private:
        void GenerateBoard();
        
        Resources *_resources;
        int GridLeft;
        int GridTop;
        std::vector<Cell*> _cells;
        std::vector<Button*> _buttons;
};