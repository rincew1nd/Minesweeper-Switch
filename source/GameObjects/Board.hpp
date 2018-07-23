#pragma once

#include <stdio.h>
#include <vector>
#include <random>
#include <switch.h>
#include <SDL2/SDL.h>

#include "../GameObjects/Cell.hpp"

#include "../Engine/Defaults.hpp"
#include "../Engine/Resources.hpp"
#include "../Engine/Input.hpp"

class Board
{
    public:
        Board(Resources*);
        bool CheckState();
        bool IsOnBoard(int, int);
        void OpenAll();
        void Restart();
        void Draw(SDL_Renderer*);
        void HandleClick(TouchInfo*);
        void Move(int, int);

        bool NeedRestart = false;
        bool NeedHardRestart = false;
        bool GameOver = false;
        
        int MineCount = 0;
        int FlagCount = 0;

      private:
        void GenerateBoard();
        void GenerateMinefield();
        Cell* GetCell(int, int);
        
        int _gridLeft;
        int _gridTop;
        int _boardHeight;
        int _boardWidth;
        Resources *_resources;
        std::vector<Cell*> _cells;
};