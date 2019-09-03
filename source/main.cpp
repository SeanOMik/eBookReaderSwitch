#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <switch.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <twili.h>

extern "C" {
    #include "common.h"
    //#include "SDL_helper.h"
    #include "textures.h"
    #include "MenuChooser.h"
}

SDL_Renderer* RENDERER;
SDL_Window* WINDOW;
SDL_Surface* WINDOW_SURFACE;
TTF_Font* ARIAL;
SDL_Event EVENT;

bool run = true;

void Term_Services() {
    std::cout << "Terminate Serices" << std::endl;

    timeExit();
    TTF_CloseFont(ARIAL);
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
    timeInitialize();
    twiliInitialize();
    std::cout << "Initalize Serices" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        Term_Services();
    }
    std::cout << "Initalized SDL" << std::endl;

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        Term_Services();
    }
    std::cout << "Initalized TTF" << std::endl;

    WINDOW = SDL_CreateWindow("sdl2_gles2", 0, 0, 1280, 720, 0);
    if (!WINDOW) {
        SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
        Term_Services();
    }
    std::cout << "Initalized Window" << std::endl;

    RENDERER = SDL_CreateRenderer(WINDOW, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!RENDERER) {
        SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
        Term_Services();
    }
    std::cout << "Initalized Renderer" << std::endl;

    WINDOW_SURFACE = SDL_GetWindowSurface(WINDOW);
    std::cout << "Retrevied Window Surface" << std::endl;

    romfsInit();
    std::cout << "Initalized RomFs" << std::endl;

    /*std::cout << "Loading Textures" << std::endl;
    Textures_Load();
    std::cout << "Loaded Textures" << std::endl;*/

    ARIAL = TTF_OpenFont("romfs:/resources/images/arial.ttf", 35);
    if (!ARIAL) {
        Term_Services();
    }
    std::cout << "Gotten Fonts" << std::endl;
    
    for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) {
            SDL_Log("SDL_JoystickOpen: %s\n", SDL_GetError());
            Term_Services();
        }
    }
    std::cout << "Initalized Input" << std::endl;
}

int main(int argc, char *argv[]) {
    Init_Services();

    //std::cout << "Opening test.pdf" << std::endl;
    //Menu_OpenBook("/switch/eBookReader/books/test.pdf");
    //Menu_OpenBook("/switch/eBookReader/books/test.epub");
    Menu_StartChoosing();

    bool isBookReading = false;
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
        /*if (!isBookReading) {
            SDL_ClearScreen(RENDERER, WHITE);
            std::cout << "Cleared Screen" << std::endl;
            SDL_RenderClear(RENDERER);
            std::cout << "Render Clear" << std::endl;*/

            /*int space_index = 0;
            while ((entry = readdir(dir)) != NULL) {
                SDL_DrawText(RENDERER, ARIAL, 20, 20 + (30 * space_index), BLACK, entry->d_name);
                space_index++;
                //cout << entry->d_name << endl;
            }*/

            /*SDL_DrawText(RENDERER, ARIAL, 50, 50, BLACK, "TEST");
            std::cout << "Draw text" << std::endl;

            SDL_RenderPresent(RENDERER);
            std::cout << "Render Present" << std::endl;
        }*/
    }

    Term_Services();
    return 0;
}
