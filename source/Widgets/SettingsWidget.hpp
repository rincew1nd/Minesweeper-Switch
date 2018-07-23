#pragma once

#include "../Engine/Widget.hpp"
#include "../Engine/Resources.hpp"

class SettingsWidget : public Widget
{
    public:
        SettingsWidget(int, int, int, int, Resources*, bool*);
};