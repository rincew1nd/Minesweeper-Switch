#include "GameScene.hpp"

GameScene::GameScene(Resources* resources)
{
    _resources = resources;

    _board = new Board(_resources);

    _widgets.push_back((Widget*)new SettingsWidget(410, 90, 450, 540, _resources, &(_board->NeedHardRestart)));
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
    for (int i = 0; i < _textes.size(); i++)
        _textes[i]->Draw(renderer);
}

void GameScene::HandleClick(TouchInfo* ti)
{
    switch (ti->Type)
    {
        case 1:
        {
            int widgetVisible = false;
            int guiClick = false;
            for (int i = 0; i < _widgets.size(); i++)
                if (_widgets[i]->IsVisible)
                {
                    _widgets[i]->HandleTouch(ti);
                    widgetVisible = true;
                }
            if (!widgetVisible)
            {
                for (int i = 0; i < _buttons.size(); i++)
                    if (_buttons[i]->Hovered(ti) && _buttons[i]->IsVisible())
                    {
                        _buttons[i]->Press();
                        guiClick = true;
                    }
                    
                if (!guiClick)
                {
                    _board->HandleClick(ti);
                    if (_board->GameOver)
                    {
                        ((GameOverWidget*)_widgets[1])->Show(false);
                        _board->GameOver = false;
                    }
                }
            }
            if (_board->CheckState())
            {
                ((GameOverWidget*)_widgets[1])->Show(true);
                _board->NeedRestart = true;
            }
            _textes[0]->Text = std::to_string(_board->MineCount - _board->FlagCount);
            break;
        }
        case 2:
            _board->Move(ti->ValueOne, ti->ValueTwo);
            break;
        case 3:
            Globals::CellSize += ti->ValueOne;
            break;
    }
}

void GameScene::InitButtons()
{
    TextObject* textObject = new TextObject(60, 700, _resources->GetFont());
    textObject->Text = std::to_string(_board->MineCount - _board->FlagCount);
    _textes.push_back(textObject);

    Button* button = new Button(545, 665, 50, 50, "restartButton");
    button->SetTexture(_resources->GetTexture(button->GetName()));
    button->SetAction([this](){ this->GetBoard()->NeedRestart = true; });
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