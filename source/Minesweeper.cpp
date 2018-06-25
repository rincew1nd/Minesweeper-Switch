#include "Minesweeper.hpp"

Minesweeper::Minesweeper()
{
    InitSDL();
    InitGame();
}

void Minesweeper::InitGame()
{
    printf("Init input\n");
    _input = new Input();

    printf("Init ROMFS\n");
    Result rc = romfsInit();
    if (R_FAILED(rc))
        printf("ERROR: romfsInit: %08X\n", rc);
    else
    {
        _resources = new Resources();
        _resources->LoadROMFS(_renderer);
    }

    printf("Init board\n");
    _board = new Board(1280, 720, _resources);
}

void Minesweeper::InitSDL()
{
    printf("Initialize SDL");
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
        if (_input->Scan())
        {
            _board->HandleClick(_input->GetPointPosition(0));
            hidScanInput();
            u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
            if (kDown) printf("test123\n");
            if (kDown & KEY_PLUS) break;
        }

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
    printf("Destroy window");
    SDL_DestroyWindow(_window);

    printf("Quit SDL subsystems");
    SDL_Quit();
}