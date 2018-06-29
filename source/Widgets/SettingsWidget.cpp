#include "SettingsWidget.hpp"

SettingsWidget::SettingsWidget(int x, int y, int w, int h, Resources* res) : Widget(x, y, w, h)
{
    SetColor(202, 202, 255);

    Button* backButton = new Button(x + w - 70, h + 20, 50, 50, "SettingsBack");
    backButton->AddTexture(res->GetTexture("restartButton"));
    backButton->SetTexture(0);
    backButton->SetAction([this]{ this->IsVisible = false; });
    _buttons.push_back(backButton);
    
    backButton = new Button(x + 20, h + 20, 50, 50, "SettingsBack");
    _buttons.push_back(backButton);
}