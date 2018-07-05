#include "GameScene.hpp"

GameScene::GameScene(Resources* resources)
{
    _resources = resources;

    _board = new Board(Globals::BoardWidth, Globals::BoardHeight, _resources);

    _widgets.push_back((Widget*)new SettingsWidget(490, 200, 450, 350, _resources));
    _widgets[0]->SetColor(152, 120, 24);
    _widgets.push_back((Widget*)new GameOverWidget(490, 250, 300, 100, _resources));
    _widgets[1]->SetColor(152, 120, 24);

    InitButtons();
}

void GameScene::Draw(SDL_Renderer* renderer)
{
    _board->Draw(renderer);
    for (int i = 0; i < _buttons.size(); i++)
        _buttons[i]->Draw(renderer);
    for (int i = 0; i < _widgets.size(); i++)
        _widgets[i]->Draw(renderer);
}

void GameScene::HandleClick(touchPosition* point)
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
        for (int i = 0; i < _buttons.size(); i++)
            if (_buttons[i]->Hovered(point) && _buttons[i]->IsVisible())
                _buttons[i]->Press();

        _board->HandleClick(point);
        
        if (_board->NeedRestart)
            _board->Restart();
    }

    if (_board->IsAllOpened())
    {
        ((GameOverWidget*)_widgets[1])->Show(true);
        _board->Restart();
    }
}

void GameScene::InitButtons()
{
    Button* button = new Button(545, 665, 50, 50, "restartButton");
    button->SetTexture(_resources->GetTexture(button->GetName()));
    button->SetAction([this](){ this->GetBoard()->Restart(); });
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

    button = new Button(800, 665, 50, 50, "settingsButton");
    button->SetTexture(_resources->GetTexture(button->GetName()));
    button->SetAction([this](){ this->GetBoard()->Move(10, 10); });
    _buttons.push_back(button);
}