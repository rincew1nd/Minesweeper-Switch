#include <switch.h>
#include "SDL2/SDL.h"
#include <vector>

#include "Resources.hpp"
#include "Engine/SpriteObject.hpp"
#include "Defaults.hpp"

class Cell : public SpriteObject
{
    public:
        Cell(int, int, int, int, Resources*);
        void AddNearCell(Cell*);
        CellState GetState();
        bool SetState(CellState);
        void SetMineTexture(SDL_Texture*);
        int NearMinesCount;
        void Reset();

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