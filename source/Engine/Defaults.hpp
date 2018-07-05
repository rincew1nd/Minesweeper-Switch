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
        static int WindowWidth;
        static int WindowHeight;

        static bool IsFlag;

        static int Dificulty;
    private:
        Globals() {}
};