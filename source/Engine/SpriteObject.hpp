#pragma once

#include "GraphicalObject.hpp"

class SpriteObject : public GraphicalObject
{
    public:
        SpriteObject(int, int, int, int);
        void Draw(SDL_Renderer*);
        void SetTexture(SDL_Texture*);
        void SetTexture(int);
        void AddTexture(SDL_Texture*);
        bool AddTexture(SDL_Texture*, int);

    protected:
        SDL_Texture* _texture = nullptr;;
        std::vector<SDL_Texture*> _textures;
};