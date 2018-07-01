#include "GameOverWidget.hpp"

GameOverWidget::GameOverWidget(int x, int y, int w, int h, Resources* res) : Widget(x, y, w, h)
{
    //Place window in center of screen
    //*_widgetPosition = {};

    TextObject* textObject = new TextObject(x+w/2, y+50, res->GetFont());
    _textes.push_back(textObject);
    
    Button* button = new Button(x, y, w, h, "escButton");
    button->SetColor(152, 120, 24);
    button->SetAction([this]{ this->IsVisible = false; });
    _buttons.push_back(button);
}

void GameOverWidget::Show(bool win)
{
    IsVisible = true;
    _textes[0]->Text = win ? "YOU WON" : "GAME OVER";
}