#include "Cell.hpp"

Cell::Cell(int posX, int posY, int dX, int dY) : SpriteObject(posX * Globals::CellSize + dX, posY * Globals::CellSize + dY, Globals::CellSize, Globals::CellSize)
{
    NearMinesCount = 0;
    _state = Closed;
    SetColor(0, 0, 0);
    SetTexture(0);
}

void Cell::AddNearCell(Cell* cell)
{
    _nearCells.push_back(cell);
}

CellState Cell::GetState()
{
    return _state;
}

bool Cell::SetState(CellState state)
{
    switch (state)
    {
        case Closed:
            _state = Closed;
            SetTexture(0);
            return true;
        case Opened:
            if (_state != Opened && _state != Flagged)
            {
                _state = Opened;
                SetTexture(2);
                if (NearMinesCount == 9)
                    return false;
                if (NearMinesCount == 0)
                    for (unsigned long i = 0; i < _nearCells.size(); i++)
                        if (_nearCells[i]->GetState() == Closed)
                            _nearCells[i]->SetState(Opened);
            }
            return true;
        case Flagged:
            switch (_state)
            {
                case Closed:
                    _state = Flagged;
                    SetTexture(1);
                    break;
                case Flagged:
                    _state = Closed;
                    SetTexture(0);
                    break;
                default:
                    break;
            }
            return true;
        default:
            printf("Something strange happend in Cell::SetState %d", state);
            return false;
    }
}

void Cell::Reset()
{
    NearMinesCount = 0;
    _state = Closed;
    _nearCells.clear();
    SetTexture(0);
}