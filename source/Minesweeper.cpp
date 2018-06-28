#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
{
    InitSDL();
    InitGame();
}

void Minesweeper::InitGame()
{
    _input = new Input();

    Result rc = romfsInit();
    if (R_FAILED(rc))
        printf("ERROR: romfsInit: %08X\n", rc);
    else
    {
        _resources = new Resources();
        _resources->LoadROMFS(_renderer);
    }

    _board = new Board(1280, 720, _resources);
}

void Minesweeper::InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    
    atexit(SDL_Quit);
    SDL_CreateWindowAndRenderer(1280, 720, 0, &_window, &_renderer);

    if (_window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    SDL_SetRenderDrawColor(_renderer, 208, 176, 48, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

void Minesweeper::Start()
{
    while (appletMainLoop())
    {
        //Handle touchscreen
        if (_input->Scan())
            _board->HandleClick(_input->GetPointPosition(0));

        //Handle joy-con button press
        if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) break;

        //Clear screen
        SDL_RenderClear(_renderer);

        //Render entity to screen
        _board->Draw(_renderer);

        SDL_SetRenderDrawColor(_renderer, 208, 176, 48, 255);

        //Draw screen
        SDL_RenderPresent(_renderer);

        //Pause
        SDL_Delay(16);
    }

    DeinitSDL();
}

void Minesweeper::DeinitSDL()
{
    SDL_DestroyWindow(_window);

    SDL_Quit();
}