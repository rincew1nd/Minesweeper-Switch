#pragma once

#include <switch.h>
#include "SDL2/SDL.h"
#include <vector>
#include <functional>

class GameObject
{
    public:
        GameObject(int, int, int, int);
        void SetAction(std::function<void()>);
        void Press() { if (_onPress != nullptr) _onPress(); };
        bool Hovered(touchPosition*);
        void Move(int, int);
        virtual ~GameObject() {};

    protected:
        SDL_Rect* _rect;

    private:
        std::function<void()> _onPress;
};