#pragma once

enum CellState
{
    Opened,
    Closed,
    Flagged
};

class Globals
{
    public:
        static int CellSize;
        static int BoardWidth;
        static int BoardHeight;

        static bool IsFlag;
    private:
        Globals() {}
};