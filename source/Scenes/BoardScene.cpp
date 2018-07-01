#include "BoardScene.hpp"
#include <ctime>
#include <string>

BoardScene::BoardScene(int w, int h, Resources* resources)
{
    //1280x720 -> 1200x650
    GridLeft = 40;
    GridTop = 10;

    _resources = resources;

    _widgets.push_back((Widget*)new SettingsWidget(490, 200, 450, 350, resources));
    _widgets[0]->SetColor(152, 120, 24);
    _widgets.push_back((Widget*)new GameOverWidget(490, 250, 300, 100, resources));
    _widgets[1]->SetColor(152, 120, 24);

    InitButtons();

    for (int y = 0; y < Globals::BoardHeight; y++)
        for (int x = 0; x < Globals::BoardWidth; x++)
        {
            Cell* cell = new Cell(x, y, GridLeft, GridTop);
            cell->AddTexture(_resources->GetTexture(Closed, 0));
            cell->AddTexture(_resources->GetTexture(Flagged, 0));
            cell->SetTexture(0);
            cell->SetAction([this, cell]{
                if (!cell->SetState(Globals::IsFlag ? Flagged : Opened))
                    Restart();
            });
            _cells.push_back(cell);
        }

    GenerateBoard();
}

void BoardScene::GenerateBoard()
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

Cell* BoardScene::GetCell(int x, int y)
{
    return _cells[x + y * Globals::BoardWidth];
}

bool BoardScene::IsAllOpened()
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        if (_cells[i]->NearMinesCount != 9 && _cells[i]->GetState() != Opened)
            return false;
    return true;
}

bool BoardScene::IsOnBoard(int x, int y)
{
    if (x >= 0 && x < Globals::BoardWidth)
        if (y >= 0 && y < Globals::BoardHeight)
            return true;
    return false;
}

void BoardScene::OpenAll()
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->SetState(Opened);
}

void BoardScene::Restart()
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Reset();

    GenerateBoard();
}

void BoardScene::Draw(SDL_Renderer* renderer)
{
    for (int i = 0; i < Globals::BoardWidth * Globals::BoardHeight; i++)
        _cells[i]->Draw(renderer);
    for (int i = 0; i < _buttons.size(); i++)
        _buttons[i]->Draw(renderer);
    for (int i = 0; i < _widgets.size(); i++)
        _widgets[i]->Draw(renderer);
}

void BoardScene::HandleClick(touchPosition* point)
{
    int widgetVisible = false;

    for (int i = 0; i < _widgets.size(); i++)
        if (_widgets[i]->IsVisible)
        {
            _widgets[i]->HandleTouch(point);
            widgetVisible = true;
        }

    if (!widgetVisible)
    {
        for (int i = 0; i < _cells.size(); i++)
            if (_cells[i]->Hovered(point) && _cells[i]->IsVisible())
            {
                if (_cells[i]->NearMinesCount == 9 && !Globals::IsFlag)
                    ((GameOverWidget*)_widgets[1])->Show(false);
                _cells[i]->Press();
            }

        for (int i = 0; i < _buttons.size(); i++)
            if (_buttons[i]->Hovered(point) && _buttons[i]->IsVisible())
                _buttons[i]->Press();
    }

    if (IsAllOpened())
    {
        ((GameOverWidget*)_widgets[1])->Show(true);
        Restart();
    }
}

void BoardScene::InitButtons()
{
    Button* button = new Button(545, 665, 50, 50, "restartButton");
    button->SetTexture(_resources->GetTexture(button->GetName()));
    button->SetAction([this](){ Restart(); });
    _buttons.push_back(button);

    button = new Button(615, 665, 50, 50, "flagButton");
    button->AddTexture(_resources->GetTexture("flagOnButton"));
    button->AddTexture(_resources->GetTexture("flagOffButton"));
    button->SetTexture(1);
    button->SetAction([button]{
        Globals::IsFlag = !Globals::IsFlag;
        button->SetTexture(Globals::IsFlag ? 0 : 1);
    });
    _buttons.push_back(button);

    button = new Button(685, 665, 50, 50, "settingsButton");
    button->SetTexture(_resources->GetTexture(button->GetName()));
    Widget* settings = _widgets[0];
    button->SetAction([settings] { settings->IsVisible = true; });
    _buttons.push_back(button);
}