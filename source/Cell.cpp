#include "Cell.hpp"

Cell::Cell(int posX, int posY, int dX, int dY, Resources* res)
    : GraphicalObject(posX * Globals::CellSize + dX, posY * Globals::CellSize + dY, Globals::CellSize, Globals::CellSize)
{
    posi = posX;
    posj = posY;
    
    NearMinesCount = 0;
    _state = Closed;
    SetColor(0, 0, 0);
    _closedTexture = res->GetTexture(Closed, 0);
    _flaggedTexture = res->GetTexture(Flagged, 0);
    SetTexture(_closedTexture);
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
            SetTexture(_closedTexture);
            return true;
        case Opened:
            if (_state != Opened && _state != Flagged)
            {
                _state = Opened;
                SetTexture(_openedTexture);
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
                    SetTexture(_flaggedTexture);
                    break;
                case Flagged:
                    _state = Closed;
                    SetTexture(_closedTexture);
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

void Cell::SetMineTexture(SDL_Texture* texture)
{
    _openedTexture = texture;
}

void Cell::Reset()
{
    NearMinesCount = 0;
    _state = Closed;
    _nearCells.clear();
    SetTexture(_closedTexture);
}