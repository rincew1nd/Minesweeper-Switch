#pragma once

#include <stdio.h>
#include <vector>
#include <random>
#include <switch.h>
#include <SDL2/SDL.h>

#include "../GameObjects/Cell.hpp"

#include "../Engine/Defaults.hpp"
#include "../Engine/Resources.hpp"
#include "../Engine/Button.hpp"
#include "../Widgets/SettingsWidget.hpp"

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
        
        int GridLeft;
        int GridTop;
        Resources *_resources;
        std::vector<Cell*> _cells;
        std::vector<Button*> _buttons;
        std::vector<Widget*> _widgets;
};