#include <switch.h>

#include "DrawableObject.hpp"
#include "Defaults.hpp"

class Cell : public DrawableObject
{
    public:
        Cell(int, int, int, int);
        void AddNearCell(Cell*);
        CellState GetState();
        bool Open();
        void FlagCell();
        void Close();
        int NearMinesCount;
    private:
        Cell();
        CellState _state;
        Cell* _nearCells[9];
};