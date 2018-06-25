#include "Board.hpp"
#include <ctime>
#include <string>

Board::Board(int w, int h, Resources* resources)
{
    //1280x720 -> 1200x650
    GridLeft = 40;
    GridTop = 10;

    _resources = resources;

    printf("Init buttons\n");
    InitButtons();

    printf("Fill array of cells\n");
    for (int y = 0; y < Globals::BoardHeight; y++)
        for (int x = 0; x < Globals::BoardWidth; x++)
            _cells.push_back(new Cell(x, y, GridLeft, GridTop, _resources));

    printf("Generate board\n");
    GenerateBoard();
}

void Board::GenerateBoard()
{
    printf("Random mines\n");
    srand(time(0));
    for (int mineCount = 0; mineCount <= Globals::BoardHeight * Globals::BoardWidth * Globals::Dificulty; mineCount++)
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
                    {
                        GetCell(i, j)->AddNearCell(GetCell(di, dj));
                        if (GetCell(di, dj)->NearMinesCount == 9 && GetCell(i, j)->NearMinesCount != 9)
                            GetCell(i, j)->NearMinesCount++;
                    }
    
    printf("Set textures\n");
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->SetMineTexture(_resources->GetTexture(Opened, _cells[i]->NearMinesCount));

    printf("Done!\n");
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
    printf("Clear near cell count\n");
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Reset();

    GenerateBoard();
}

void Board::Draw(SDL_Renderer* renderer)
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Draw(renderer);
    for (unsigned long i = 0; i < _buttons.size(); i++)
        _buttons[i]->Draw(renderer);
}

void Board::HandleClick(touchPosition* point)
{
    int x = (point->px - GridLeft);
    x = x / Globals::CellSize;
    int y = (point->py - GridTop);
    y = y / Globals::CellSize;

    if (IsOnBoard(x, y))
        if (!GetCell(x, y)->SetState(Globals::IsFlag ? Flagged : Opened))
            Restart();

    for (int i = 0; i < _buttons.size(); i++)
        if (point->px >= _buttons[i]->GetRect()->x && point->px <= _buttons[i]->GetRect()->x + _buttons[i]->GetRect()->w &&
            point->py >= _buttons[i]->GetRect()->y && point->py <= _buttons[i]->GetRect()->y + _buttons[i]->GetRect()->h &&
            _buttons[i]->IsVisible())
            if (_buttons[i]->Name == "restart")
            {
                Restart();
                break;
            }
            else if (_buttons[i]->Name == "flagOnButton")
            {
                Globals::IsFlag = true;
                _buttons[1]->SetVisible(false);
                _buttons[2]->SetVisible(true);
                break;
            }
            else if (_buttons[i]->Name == "flagOffButton")
            {
                Globals::IsFlag = false;
                _buttons[2]->SetVisible(false);
                _buttons[1]->SetVisible(true);
                break;
            }
            else if (_buttons[i]->Name == "hardButton")
            {
                printf("hard\n");
                Globals::Dificulty = 0.2f;
                _buttons[i]->SetVisible(false);
                _buttons[i+1]->SetVisible(true);
                Restart();
                break;
            }
            else if (_buttons[i]->Name == "mediumButton")
            {
                printf("medium\n");
                Globals::Dificulty = 0.1f;
                _buttons[i]->SetVisible(false);
                _buttons[i+1]->SetVisible(true);
                Restart();
                break;
            }
            else if (_buttons[i]->Name == "easyButton")
            {
                printf("easy\n");
                Globals::Dificulty = 0.3f;
                _buttons[i]->SetVisible(false);
                _buttons[i-2]->SetVisible(true);
                Restart();
                break;
            }
}

void Board::InitButtons()
{
    Button* button = new Button(580, 665, 50, 50, "restartButton");
    button->SetTexture(_resources->GetTexture(button->Name));
    _buttons.push_back(button);

    button = new Button(650, 665, 50, 50, "flagOnButton");
    button->SetTexture(_resources->GetTexture(button->Name));
    _buttons.push_back(button);

    button = new Button(650, 665, 50, 50, "flagOffButton");
    button->SetTexture(_resources->GetTexture(button->Name));
    button->SetVisible(false);
    _buttons.push_back(button);

    button = new Button(300, 665, 100, 50, "hardButton");
    button->SetTexture(_resources->GetTexture(button->Name));
    button->SetVisible(true);
    _buttons.push_back(button);
    
    button = new Button(300, 665, 100, 50, "mediumButton");
    button->SetTexture(_resources->GetTexture(button->Name));
    button->SetVisible(false);
    _buttons.push_back(button);
    
    button = new Button(300, 665, 100, 50, "easyButton");
    button->SetTexture(_resources->GetTexture(button->Name));
    button->SetVisible(false);
    _buttons.push_back(button);
}