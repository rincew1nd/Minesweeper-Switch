#include <switch.h>
#include <SDL2/SDL.h>

class Button
{
    public:
        Button(int, int, int, int);
        void SetColor(int, int, int, int);
        void SetColor(int, int, int);
        void Draw(SDL_Renderer*);
    private:
        SDL_Rect *rect;
        SDL_Color *color;
};