#pragma once

#include "../Engine/Widget.hpp"
#include "../Engine/Resources.hpp"

class GameOverWidget : public Widget
{
    public:
        GameOverWidget(int, int, int, int, Resources*);
        void Show(bool);
};