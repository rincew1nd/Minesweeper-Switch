#include "SpriteObject.hpp"

SpriteObject::SpriteObject(int x, int y, int w, int h) : GraphicalObject(x, y, w, h) {}

void SpriteObject::Draw(SDL_Renderer *renderer)
{
    if (_isVisible)
    {
        SDL_SetRenderDrawColor(renderer, _color->r, _color->g, _color->b, _color->a);
        if (_texture != NULL)
            SDL_RenderCopy(renderer, _texture, NULL, _rect);
        else
            SDL_RenderFillRect(renderer, _rect);
    }
}

void SpriteObject::SetTexture(SDL_Texture* texture)
{
    _texture = texture;
}