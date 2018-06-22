#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
{
    InitSDL();
    InitGame();

    while (true)
    {
        if (_input->Scan())
        {
            _board->HandleClick(_input->GetPointPosition(0));
        }
        
        //Clear screen
        SDL_RenderClear(_renderer);

        //Render entity to screen
        _board->Draw(_renderer);

        SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

        //Draw screen
        SDL_RenderPresent(_renderer);

        //Pause
        SDL_Delay(16);
    }

    DeinitSDL();

    return;
}

void Minesweeper::InitGame()
{
    Globals::CellSize = 50;
    Globals::BoardWidth = 24;
    Globals::BoardHeight = 13;

    printf("Init input\n");
    _input = new Input();

    printf("Init board\n");
    _board = new Board(1280, 720);
}

void Minesweeper::InitSDL()
{
    printf("Initialize SDL");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    printf("Test!\n");
    
    atexit(SDL_Quit);
    SDL_CreateWindowAndRenderer(1280, 720, 0, &_window, &_renderer);

    if (_window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

void Minesweeper::DeinitSDL()
{
    printf("Destroy window");
    SDL_DestroyWindow(_window);

    printf("Quit SDL subsystems");
    SDL_Quit();
}