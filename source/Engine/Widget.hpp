#pragma once

#include "Button.hpp"
#include <SDL2/SDL_ttf.h>

class Widget
{
    public:
        Widget(int, int, int, int);
        void HandleTouch(touchPosition*);
        void HandleJoystick() {};
        
        bool IsVisible;
        void SetColor(int, int, int, int);
        void SetColor(int, int, int);
        void SetTexture(SDL_Texture*);
        void SetFont(TTF_Font*);
        void Draw(SDL_Renderer*);
        virtual ~Widget() {};

    protected:
        SDL_Rect* _widgetPosition;
        SDL_Color* _widgetBackgroundColor;
        SDL_Texture* _widgetBackgroundTexture = nullptr;
        TTF_Font* _font;
        std::vector<Button*> _buttons;
};