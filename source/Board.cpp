#include "Board.hpp"

Board::Board(int w, int h)
{
    //1280x720 -> 1200x650
    GridLeft = 40;
    GridTop = 10;

    printf("Fill array of cells\n");
    for (int x = 0; x < Globals::BoardWidth; x++)
        for (int y = 0; y < Globals::BoardHeight; y++)
            _cells.push_back(new Cell(x, y, GridLeft, GridTop));
            
    printf("Generate board\n");
    GenerateBoard();
}

void Board::GenerateBoard()
{

    printf("Random mines\n");
    srand(2);
    for (int mineCount = 0; mineCount <= Globals::BoardHeight * Globals::BoardWidth * 0.3; mineCount++)
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

    printf("Fill neighbors\n");
    for (int i = 0; i < Globals::BoardWidth; i++)
        for (int j = 0; j < Globals::BoardHeight; j++)
            for (int di = i-1; di <= i+1; di++)
                for (int dj = j-1; dj <= j+1; dj++)
                    if (!(di==i && dj==j) && IsOnBoard(di, dj))
                        GetCell(i, j)->AddNearCell(GetCell(di, dj));
}

Cell* Board::GetCell(int x, int y)
{
    return _cells[x + y * Globals::BoardWidth];
}

bool Board::IsAllOpened()
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        if (_cells[i]->GetState() != Opened || _cells[i]->GetState() != Flagged)
            return false;
    return true;
}

bool Board::IsOnBoard(int x, int y)
{
    if (x > 0 && x < Globals::BoardWidth)
        if (y > 0 && y < Globals::BoardHeight)
            return true;
    return false;
}

void Board::OpenAll()
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Open();
}

void Board::Restart()
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Close();
}

void Board::Draw(SDL_Renderer* renderer)
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Draw(renderer);
}

void Board::HandleClick(touchPosition* point)
{
    int x = (point->px - GridLeft) / Globals::CellSize;
    int y = (point->py - GridTop) / Globals::CellSize;

    if (IsOnBoard(x, y))
    {
        printf("Click %03d;%03d -> %03d;%03d\n", point->px, point->py, GetCell(x, y)->GetX(), GetCell(x, y)->GetY());
        GetCell(x, y)->Open();
    }
}