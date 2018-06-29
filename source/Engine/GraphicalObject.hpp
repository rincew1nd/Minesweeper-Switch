#pragma once

#include "GameObject.hpp"

class GraphicalObject : public GameObject
{
    public:
        GraphicalObject(int, int, int, int);
        void SetColor(int, int, int, int);
        void SetColor(int, int, int);
        void Draw(SDL_Renderer*);
        SDL_Rect* GetRect();
        void SetVisible(bool);
        bool IsVisible();

    protected:
        SDL_Color* _color;
        bool _isVisible;
};