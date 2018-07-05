#include "Board.hpp"
#include <ctime>
#include <string>

Board::Board(int w, int h, Resources* resources)
{
    GridLeft = (Globals::WindowWidth - Globals::BoardWidth * Globals::CellSize) / 2;
    GridTop = (Globals::WindowHeight - Globals::BoardHeight * Globals::CellSize) / 2;

    _resources = resources;

    for (int y = 0; y < Globals::BoardHeight; y++)
        for (int x = 0; x < Globals::BoardWidth; x++)
        {
            Cell* cell = new Cell(x, y, GridLeft, GridTop);
            cell->AddTexture(_resources->GetTexture(Closed, 0));
            cell->AddTexture(_resources->GetTexture(Flagged, 0));
            cell->SetTexture(0);
            cell->SetAction([this, cell]{
                if (!cell->SetState(Globals::IsFlag ? Flagged : Opened))
                    NeedRestart = true;
            });
            _cells.push_back(cell);
        }

    GenerateBoard();
}

void Board::GenerateBoard()
{
    srand(time(0));
    for (int mineCount = 0; mineCount <= Globals::BoardHeight * Globals::BoardWidth * 0.1f * Globals::Dificulty; mineCount++)
    {
        while(true)
        {
            int posX = rand() % Globals::BoardWidth;
            int posY = rand() % Globals::BoardHeight;

            if (GetCell(posX, posY)->NearMinesCount != 9)
            {
                GetCell(posX, posY)->NearMinesCount = 9;
                break;
            }
        }
    }

    for (int i = 0; i < Globals::BoardWidth; i++)
        for (int j = 0; j < Globals::BoardHeight; j++)
            for (int di = i-1; di <= i+1; di++)
                for (int dj = j-1; dj <= j+1; dj++)
                    if (!(di==i && dj==j) && IsOnBoard(di, dj))
                    {
                        GetCell(i, j)->AddNearCell(GetCell(di, dj));
                        if (GetCell(di, dj)->NearMinesCount == 9 && GetCell(i, j)->NearMinesCount != 9)
                            GetCell(i, j)->NearMinesCount++;
                    }
    
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->AddTexture(_resources->GetTexture(Opened, _cells[i]->NearMinesCount), 2);
}

Cell* Board::GetCell(int x, int y)
{
    return _cells[x + y * Globals::BoardWidth];
}

bool Board::IsAllOpened()
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        if (_cells[i]->NearMinesCount != 9 && _cells[i]->GetState() != Opened)
            return false;
    return true;
}

bool Board::IsOnBoard(int x, int y)
{
    if (x >= 0 && x < Globals::BoardWidth)
        if (y >= 0 && y < Globals::BoardHeight)
            return true;
    return false;
}

void Board::OpenAll()
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->SetState(Opened);
}

void Board::Restart()
{
    NeedRestart = false;

    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Reset();

    GenerateBoard();
}

void Board::Draw(SDL_Renderer* renderer)
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Draw(GridLeft, GridTop, renderer);
}

void Board::HandleClick(touchPosition* point)
{
    for (int i = 0; i < _cells.size(); i++)
        if (_cells[i]->Hovered(point) && _cells[i]->IsVisible())
            _cells[i]->Press();
}

void Board::Move(int dx, int dy)
{
    GridLeft += dx;
    GridTop += dy;
}