#include "TextObject.hpp"

TextObject::TextObject(int x, int y, TTF_Font* font) : GraphicalObject(0, 0, 0, 0)
{
    _centerX = x;
    _centerY = y;
	_font = font;
}

void TextObject::SetFont(TTF_Font* font)
{
	_font = font;
}

void TextObject::Draw(SDL_Renderer* renderer)
{
	if (IsVisible())
	{
		if (_lastText != Text)
		{
			if (_texture != nullptr) SDL_DestroyTexture(_texture);
			SDL_Surface* textSurface = TTF_RenderText_Solid(_font, Text.c_str(), *_color);
			_texture = SDL_CreateTextureFromSurface(renderer, textSurface);

            //Get the size of the text and position texture on x;y center
            int w, h;
            TTF_SizeText(_font, Text.c_str(), &w, &h);
            *_rect = {_centerX-w/2, _centerY-h/2, w, h};

			SDL_FreeSurface(textSurface);
			_lastText = Text;
		}

	    SDL_RenderCopy(renderer, _texture, NULL, _rect);
	}
}

void TextObject::Move(int dx, int dy)
{
    GraphicalObject::Move(dx, dy);
    _centerX += dx;
    _centerY += dy;
}