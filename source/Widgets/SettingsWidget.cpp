#include "SettingsWidget.hpp"

SettingsWidget::SettingsWidget(int x, int y, int w, int h, Resources* res, bool* restartFlag) : Widget(x, y, w, h)
{
    TextObject* textObject = new TextObject(x+w/2, y+45, res->GetFont());
    textObject->Text = "PAUSE";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+450, res->GetFont());
    textObject->Text = "Press + to";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+500, res->GetFont());
    textObject->Text = "exit application";
    _textes.push_back(textObject);

    Button* button = new Button(x + w - 70, y + 20, 50, 50, "escButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([this]{ this->IsVisible = false; });
    _buttons.push_back(button);

    // Difficulty
    textObject = new TextObject(x+w/2, y+120, res->GetFont());
    textObject->Text = "Difficulty";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+175, res->GetFont());
    textObject->Text = std::to_string(Globals::Dificulty);
    _textes.push_back(textObject);
    
    button = new Button(x+20, y+150, 50, 50, "minusButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([textObject, restartFlag]{
        if (--Globals::Dificulty < 1)
            Globals::Dificulty = 1;
        textObject->Text = std::to_string(Globals::Dificulty);
        *restartFlag = true;
    });
    _buttons.push_back(button);
    
    button = new Button(x+w-70, y+150, 50, 50, "plusButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([textObject, restartFlag]{
        if (++Globals::Dificulty > 4)
            Globals::Dificulty = 4;
        textObject->Text = std::to_string(Globals::Dificulty);
        *restartFlag = true;
    });
    _buttons.push_back(button);

    //Board height
    textObject = new TextObject(x+w/2, y+225, res->GetFont());
    textObject->Text = "Board Height";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+275, res->GetFont());
    textObject->Text = std::to_string(Globals::BoardHeight);
    _textes.push_back(textObject);

    button = new Button(x+20, y+250, 50, 50, "minusButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([textObject, restartFlag]{
        if (--Globals::BoardHeight < 1)
            Globals::BoardHeight = 1;
        textObject->Text = std::to_string(Globals::BoardHeight);
        *restartFlag = true;
    });
    _buttons.push_back(button);
    
    button = new Button(x+w-70, y+250, 50, 50, "plusButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([textObject, restartFlag]{
        if (++Globals::BoardHeight > 40)
            Globals::BoardHeight = 40;
        textObject->Text = std::to_string(Globals::BoardHeight);
        *restartFlag = true;
    });
    _buttons.push_back(button);

    //Board width
    textObject = new TextObject(x+w/2, y+325, res->GetFont());
    textObject->Text = "Board Width";
    _textes.push_back(textObject);
    textObject = new TextObject(x+w/2, y+375, res->GetFont());
    textObject->Text = std::to_string(Globals::BoardWidth);
    _textes.push_back(textObject);

    button = new Button(x+20, y+350, 50, 50, "minusButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([textObject, restartFlag]{
        if (--Globals::BoardWidth < 1)
            Globals::BoardWidth = 1;
        textObject->Text = std::to_string(Globals::BoardWidth);
        *restartFlag = true;
    });
    _buttons.push_back(button);
    
    button = new Button(x+w-70, y+350, 50, 50, "plusButton");
    button->AddTexture(res->GetTexture(button->GetName()));
    button->SetTexture(0);
    button->SetAction([textObject, restartFlag]{
        if (++Globals::BoardWidth > 40)
            Globals::BoardWidth = 40;
        textObject->Text = std::to_string(Globals::BoardWidth);
        *restartFlag = true;
    });
    _buttons.push_back(button);
}