#include <switch.h>
#include "SDL2/SDL.h"
#include <vector>

#include "Resources.hpp"
#include "DrawableObject.hpp"
#include "Defaults.hpp"

class Cell : public DrawableObject
{
    public:
        Cell(int, int, int, int, Resources*);
        void AddNearCell(Cell*);
        CellState GetState();
        bool SetState(CellState);
        void SetMineTexture(SDL_Texture*);
        int NearMinesCount;

        int posi;
        int posj;
    private:
        Cell();
        CellState _state;
        std::vector<Cell*> _nearCells;

        SDL_Texture* _closedTexture;
        SDL_Texture* _openedTexture;
        SDL_Texture* _flaggedTexture;
};