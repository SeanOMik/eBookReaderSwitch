#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <switch.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <twili.h>

extern "C" {
    #include "common.h"
    #include "SDL_helper.h"
    #include "textures.h"
    #include "MenuChooser.h"
}

SDL_Renderer* RENDERER;
SDL_Window* WINDOW;
SDL_Surface* WINDOW_SURFACE;
TTF_Font* ARIAL_UNICODE;
SDL_Event EVENT;

bool run = true;

void Term_Services() {
    std::cout << "Terminate Serices" << std::endl;

    TTF_CloseFont(ARIAL_UNICODE);
    TTF_Quit();

    Textures_Free();
    romfsExit();

    SDL_DestroyRenderer(RENDERER);
    SDL_FreeSurface(WINDOW_SURFACE);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();

    twiliExit();
    run = false;
}

void Init_Services() {
    twiliInitialize();
    std::cout << "Initalize Serices" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        Term_Services();
    }

    TTF_Init();

    WINDOW = SDL_CreateWindow("sdl2_gles2", 0, 0, 1280, 720, 0);
    if (!WINDOW) {
        SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
        Term_Services();
    }

    RENDERER = SDL_CreateRenderer(WINDOW, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!RENDERER) {
        SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
        Term_Services();
    }

    WINDOW_SURFACE = SDL_GetWindowSurface(WINDOW);

    romfsInit();
    Textures_Load();
    ARIAL_UNICODE = TTF_OpenFont("romfs:/res/font/arial.ttf", 35);
    if (!ARIAL_UNICODE) {
        Term_Services();
    }
    
    for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) {
            SDL_Log("SDL_JoystickOpen: %s\n", SDL_GetError());
            Term_Services();
        }
    }
}

int main(int argc, char *argv[]) {
    Init_Services();

    //std::cout << "Opening test.pdf" << std::endl;
    //Menu_OpenBook("/switch/eBookReader/books/test.pdf");
    //Menu_OpenBook("/switch/eBookReader/books/test.epub");
    Menu_StartChoosing();

    while (run) {
        while (SDL_PollEvent(&EVENT)) {
            switch (EVENT.type) {
                case SDL_JOYAXISMOTION:
                    break;
                case SDL_JOYBUTTONDOWN:
                    // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L52
                    // seek for joystick #0
                    if (EVENT.jbutton.which == 0) {
                        if (EVENT.jbutton.button == 0) {
                            // (A) button down
                        } else if (EVENT.jbutton.button == 10) {
                            // (+) button down
                            run = false;
                        }
                    }
                    break;

                default:
                    break;
            }
        }
        /*SDL_ClearScreen(RENDERER, WHITE);
		SDL_RenderClear(RENDERER);

        SDL_RenderPresent(RENDERER);*/
    }

    Term_Services();
    return 0;
}
