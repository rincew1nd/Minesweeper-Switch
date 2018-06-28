#include "SpriteObject.hpp"

SpriteObject::SpriteObject(int x, int y, int w, int h) : GraphicalObject(x, y, w, h) {}

void SpriteObject::Draw(SDL_Renderer *renderer)
{
    if (_isVisible)
    {
        if (_texture != NULL)
            SDL_RenderCopy(renderer, _texture, NULL, _rect);
        else
        {
            SDL_SetRenderDrawColor(renderer, _color->r, _color->g, _color->b, _color->a);
            SDL_RenderFillRect(renderer, _rect);
        }
    }
}

void SpriteObject::AddTexture(SDL_Texture* texture)
{
    _textures.push_back(texture);
}

bool SpriteObject::AddTexture(SDL_Texture* texture, int pos)
{
    if (_textures.size() > pos)
        _textures.at(pos) = texture;
    else if (_textures.size() == pos)
        _textures.push_back(texture);
    else
        return false;
    return true;
}

void SpriteObject::SetTexture(SDL_Texture* texture)
{
    _texture = texture;
}

void SpriteObject::SetTexture(int pos)
{
    if (_textures.size() > pos)
        SetTexture(_textures.at(pos));
}