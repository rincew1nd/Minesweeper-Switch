#include "Board.hpp"
#include <ctime>
#include <string>

Board::Board(Resources* resources)
{
    _resources = resources;
    GenerateBoard();
}

void Board::GenerateBoard()
{
    _boardHeight = Globals::BoardHeight;
    _boardWidth = Globals::BoardWidth;

    _gridLeft = (Globals::WindowWidth - _boardWidth * Globals::CellSize) / 2;
    _gridTop = (Globals::WindowHeight - _boardHeight * Globals::CellSize) / 2;

    for (int y = 0; y < _boardHeight; y++)
        for (int x = 0; x < _boardWidth; x++)
        {
            Cell* cell = new Cell(x, y, _gridLeft, _gridTop);
            cell->AddTexture(_resources->GetTexture(Closed, 0));
            cell->AddTexture(_resources->GetTexture(Flagged, 0));
            cell->SetTexture(0);
            cell->SetAction([this, cell]{
                if ((cell->GetState() == Opened && !cell->OpenNearCells()) || !cell->SetState(Globals::IsFlag ? Flagged : Opened))
                {
                    NeedRestart = true;
                    GameOver = true;
                }
            });
            _cells.push_back(cell);
        }

    for (int i = 0; i < _boardWidth; i++)
        for (int j = 0; j < _boardHeight; j++)
            for (int di = i-1; di <= i+1; di++)
                for (int dj = j-1; dj <= j+1; dj++)
                    if (!(di==i && dj==j) && IsOnBoard(di, dj))
                        GetCell(i, j)->AddNearCell(GetCell(di, dj));
    
    GenerateMinefield();
}

void Board::GenerateMinefield()
{
    MineCount = 0;

    srand(time(0));
    for (int mineCount = 0; mineCount <= _boardHeight * _boardWidth * 0.1f * Globals::Dificulty; mineCount++)
    {
        while(true)
        {
            int posX = rand() % _boardWidth;
            int posY = rand() % _boardHeight;

            if (GetCell(posX, posY)->NearMinesCount != 9)
            {
                GetCell(posX, posY)->NearMinesCount = 9;
                MineCount++;
                break;
            }
        }
    }

    for (int i = 0; i < _boardWidth; i++)
        for (int j = 0; j < _boardHeight; j++)
            for (int di = i-1; di <= i+1; di++)
                for (int dj = j-1; dj <= j+1; dj++)
                    if (!(di==i && dj==j) && IsOnBoard(di, dj))
                        if (GetCell(di, dj)->NearMinesCount == 9 && GetCell(i, j)->NearMinesCount != 9)
                            GetCell(i, j)->NearMinesCount++;
    
    for (int i = 0; i < _boardWidth * _boardHeight; i++)
        _cells[i]->AddTexture(_resources->GetTexture(Opened, _cells[i]->NearMinesCount), 2);
}

Cell* Board::GetCell(int x, int y)
{
    return _cells[x + y * _boardWidth];
}

bool Board::CheckState()
{
    FlagCount = 0;
    bool allFlagsCorrect = true;
    bool allCellsOppened = true;
    
    for (int i = 0; i < _boardWidth * _boardHeight; i++)
    {
        if (_cells[i]->GetState() == Flagged)
        {
            if (_cells[i]->NearMinesCount != 9)
                allFlagsCorrect = false;
            FlagCount++;
        }
        if (_cells[i]->NearMinesCount != 9 && _cells[i]->GetState() != Opened)
            allCellsOppened = false;
    }

    allFlagsCorrect = (allFlagsCorrect) ? FlagCount == MineCount ? true : false : false;
    return allCellsOppened || allFlagsCorrect;
}

bool Board::IsOnBoard(int x, int y)
{
    if (x >= 0 && x < _boardWidth)
        if (y >= 0 && y < _boardHeight)
            return true;
    return false;
}

void Board::OpenAll()
{
    for (int i = 0; i < _boardWidth * _boardHeight; i++)
        _cells[i]->SetState(Opened);
}

void Board::Restart()
{
    if (NeedRestart)
    {
        NeedRestart = false;
        for (int i = 0; i < _boardWidth * _boardHeight; i++)
            _cells[i]->Reset();
        GenerateMinefield();
    }
    if (NeedHardRestart)
    {
        NeedHardRestart = false;
        _cells.clear();
        GenerateBoard();
    }
}

void Board::Draw(SDL_Renderer* renderer)
{
    Restart();
    for (int i = 0; i < _boardWidth * _boardHeight; i++)
        _cells[i]->Draw(_gridLeft, _gridTop, renderer);
}

void Board::HandleClick(TouchInfo* point)
{
    for (int i = 0; i < _cells.size(); i++)
        if (_cells[i]->Hovered(point) && _cells[i]->IsVisible())
            _cells[i]->Press();
}

void Board::Move(int dx, int dy)
{
    _gridLeft += dx;
    _gridTop += dy;
}