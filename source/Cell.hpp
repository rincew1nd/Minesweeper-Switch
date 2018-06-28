#include <switch.h>
#include "SDL2/SDL.h"
#include <vector>

#include "Resources.hpp"
#include "Engine/SpriteObject.hpp"
#include "Engine/TouchableObject.hpp"
#include "Defaults.hpp"

class Cell : public SpriteObject, public TouchableObject
{
    public:
        Cell(int, int, int, int);
        void AddNearCell(Cell*);
        CellState GetState();
        bool SetState(CellState);
        void Reset();

        int NearMinesCount;
        int posi;
        int posj;
    private:
        Cell();
        CellState _state;
        std::vector<Cell*> _nearCells;
};