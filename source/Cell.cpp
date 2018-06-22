#include "Cell.hpp"
#include "Defaults.hpp"

Cell::Cell(int posX, int posY, int dX, int dY)
    : DrawableObject(posX * Globals::CellSize + dX, posY * Globals::CellSize + dY, Globals::CellSize, Globals::CellSize)
{
    _state = Closed;
    SetColor(0, 0, 0);
}

void Cell::AddNearCell(Cell* cell)
{
    for (int i = 0; i < 9; i++)
        if (_nearCells[i] == NULL)
            _nearCells[i] = cell;
}

CellState Cell::GetState()
{
    return _state;
}

bool Cell::Open()
{
    if (_state != Opened)
    {
        _state = Opened;
        if (NearMinesCount == 9)
            SetColor(255, 0, 0);
            return false;
        if (_state != Flagged)
            if (NearMinesCount == 0)
                for (int i = 0; i < 9; i++)
                {
                    if (_nearCells[i] == NULL)
                        break;
                    _nearCells[i]->Open();
                }
    }
    SetColor(0, 255, 0);
    return true;
}

void Cell::FlagCell()
{
    switch (_state)
    {
        case Closed:
            _state = Flagged;
            SetColor(0, 0, 255);
            break;
        case Flagged:
            _state = Closed;
            SetColor(0, 0, 0);
            break;
        default:
            break;
    }
}

void Cell::Close()
{
    _state = Closed;
}