#pragma once
#include <switch.h>
#include <SDL2/SDL.h>

class DrawableObject
{
    public:
        DrawableObject(int, int, int, int);
        void SetColor(int, int, int, int);
        void SetColor(int, int, int);
        void Draw(SDL_Renderer*);
        SDL_Rect* GetRect();
        void SetTexture(SDL_Texture*);
        void SetVisible(bool);
        bool IsVisible();

      private:
        SDL_Rect* _rect;
        SDL_Color* _color;
        SDL_Texture* _texture;
        bool _isVisible;
};