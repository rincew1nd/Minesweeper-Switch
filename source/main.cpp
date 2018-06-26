#include <switch.h>
#include "Minesweeper.hpp"

int main(int argc, char *argv[])
{
    socketInitializeDefault();
    nxlinkStdio();

    printf("Minesweeper start!\n");

    Minesweeper* game = new Minesweeper();
    game->Start();

    printf("Minesweeper end!\n");
    socketExit();
    return 0;
}