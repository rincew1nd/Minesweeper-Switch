#pragma once

#include "../Engine/Resources.hpp"
#include "../Engine/SpriteObject.hpp"
#include "../Engine/Defaults.hpp"

class Cell : public SpriteObject
{
    public:
        Cell(int, int, int, int);
        void AddNearCell(Cell*);
        CellState GetState();
        bool SetState(CellState);
        void Reset();
        void Draw(int, int, SDL_Renderer*);

        int NearMinesCount;
    private:
        CellState _state;
        std::vector<Cell*> _nearCells;

        int _cellX, _cellY, _lastLeft, _lastTop;
};