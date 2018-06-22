#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
{
    socketInitializeDefault();
    nxlinkStdio();

    InitSDL();
    input = new Input();
    Button* button = new Button(100, 100, 100, 100);
    button->SetColor(100, 100, 100);

    while (true)
    {
        //Clear screen
        SDL_RenderClear(renderer);

        //Render entity to screen
        button->Draw(renderer);

        //Draw screen
        SDL_RenderPresent(renderer);
        
        //Pause
        SDL_Delay(16);
    }

    DeinitSDL();

    return;
}

void Minesweeper::InitSDL()
{
    printf("Initialize SDL");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    printf("Create window");
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    printf("Get window surface");
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Minesweeper::DeinitSDL()
{
    printf("Destroy window");
    SDL_DestroyWindow(window);

    printf("Quit SDL subsystems");
    //SDL_Quit();
}