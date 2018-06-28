#pragma once

#include "GraphicalObject.hpp"

class SpriteObject : public virtual GraphicalObject
{
    public:
        SpriteObject(int, int, int, int);
        void Draw(SDL_Renderer*);
        void SetTexture(SDL_Texture*);

    protected:
        SDL_Texture* _texture;
};