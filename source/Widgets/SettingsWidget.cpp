#include "SettingsWidget.hpp"

SettingsWidget::SettingsWidget(int x, int y, int w, int h, Resources* res) : Widget(x, y, w, h)
{
    //Place window in center of screen
    //*_widgetPosition = {};

    TextObject* textObject = new TextObject(x+w/2, y+45, res->GetFont());
    textObject->Text = "PAUSE";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+120, res->GetFont());
    textObject->Text = "Difficulty";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+270, res->GetFont());
    textObject->Text = "Press + to";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+305, res->GetFont());
    textObject->Text = "exit application";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+175, res->GetFont());
    textObject->Text = std::to_string(Globals::Dificulty);
    _textes.push_back(textObject);

    Button* button = new Button(x + w - 70, y + 20, 50, 50, "escButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([this]{ this->IsVisible = false; });
    _buttons.push_back(button);
    
    button = new Button(x+20, y+150, 50, 50, "minusButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([textObject]{
        if (--Globals::Dificulty < 1)
            Globals::Dificulty = 1;
        textObject->Text = std::to_string(Globals::Dificulty);
    });
    _buttons.push_back(button);
    
    button = new Button(x+w-70, y+150, 50, 50, "plusButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([textObject]{
        if (++Globals::Dificulty > 4)
            Globals::Dificulty = 4;
        textObject->Text = std::to_string(Globals::Dificulty);
    });
    _buttons.push_back(button);
}