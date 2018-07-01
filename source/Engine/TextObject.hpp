#include "GraphicalObject.hpp"

#include <SDL2/SDL_ttf.h>

class TextObject : public GraphicalObject
{
	public:
		TextObject(int, int, TTF_Font*);
		void SetFont(TTF_Font*);
        void Move(int, int);
        void Draw(SDL_Renderer*);
		std::string Text;

	protected:
        int _centerX, _centerY;
		std::string _lastText;
		TTF_Font* _font = nullptr;
        SDL_Texture* _texture = nullptr;
};