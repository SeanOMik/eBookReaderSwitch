#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <switch.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <twili.h>

extern "C" {
    #include "menu_book_reader.h"
    #include "common.h"
    #include "SDL_helper.h"
}

/*void draw_rects(SDL_Renderer *renderer, int x, int y) {
    // R
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect r = {x, y, 64, 64};
    SDL_RenderFillRect(renderer, &r);

    // G
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect g = {x + 64, y, 64, 64};
    SDL_RenderFillRect(renderer, &g);

    // B
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect b = {x + 128, y, 64, 64};
    SDL_RenderFillRect(renderer, &b);
}*/

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

    romfsExit();

    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();

    //socketExit();
    twiliExit();
    run = false;
}

void Init_Services() {
    twiliInitialize();
    /*socketInitializeDefault();
	nxlinkStdio();*/
    std::cout << "Initalize Serices" << std::endl;

    // mandatory at least on switch, else gfx is not properly closed
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        Term_Services();
    }

    TTF_Init();

    // create an SDL WINDOW (OpenGL ES2 always enabled)
    // when SDL_FULLSCREEN flag is not set, viewport is automatically handled by SDL (use SDL_SetWINDOWSize to "change resolution")
    // available switch SDL2 video modes :
    // 1920 x 1080 @ 32 bpp (SDL_PIXELFORMAT_RGBA8888)
    // 1280 x 720 @ 32 bpp (SDL_PIXELFORMAT_RGBA8888)
    WINDOW = SDL_CreateWindow("sdl2_gles2", 0, 0, 1920, 1080, 0);
    if (!WINDOW) {
        SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
        Term_Services();
    }

    // create a renderer (OpenGL ES2)
    RENDERER = SDL_CreateRenderer(WINDOW, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!RENDERER) {
        SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
        Term_Services();
    }

    // Get a reference to the window surface
    // This has to be ran after you create the renderer.
    WINDOW_SURFACE = SDL_GetWindowSurface(WINDOW);

    romfsInit();

    ARIAL_UNICODE = TTF_OpenFont("romfs:/arial-unicode-ms.ttf", 30);
    if (!ARIAL_UNICODE) {
        Term_Services();
    }

    // open CONTROLLER_PLAYER_1 and CONTROLLER_PLAYER_2
    // when railed, both joycons are mapped to joystick #0,
    // else joycons are individually mapped to joystick #0, joystick #1, ...
    // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L45
    for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) {
            SDL_Log("SDL_JoystickOpen: %s\n", SDL_GetError());
            Term_Services();
        }
    }
}

int main(int argc, char *argv[]) {
    /*SDL_Renderer* RENDERER; 
    SDL_Window* WINDOW;
    SDL_Surface* WINDOW_SURFACE;
    TTF_Font* ARIAL_UNICODE;*/
    //int x = 0, w = 1920, h = 1080;

    Init_Services();

    std::cout << "Opening test.epub" << std::endl;
    Menu_OpenBook("/switch/eBookReader/books/test.pdf");
    //Menu_OpenBook("/switch/eBookReader/books/test.epub");

    while (run) {
        while (SDL_PollEvent(&EVENT)) {
            switch (EVENT.type) {
                case SDL_JOYAXISMOTION:
                    SDL_Log("Joystick %d axis %d value: %d\n",
                            EVENT.jaxis.which,
                            EVENT.jaxis.axis, EVENT.jaxis.value);
                    break;
                case SDL_JOYBUTTONDOWN:
                    SDL_Log("Joystick %d button %d down\n",
                            EVENT.jbutton.which, EVENT.jbutton.button);
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

    /*while (!done) {
        while (SDL_PollEvent(&EVENT)) {
            switch (EVENT.type) {
                case SDL_JOYAXISMOTION:
                    SDL_Log("Joystick %d axis %d value: %d\n",
                            EVENT.jaxis.which,
                            EVENT.jaxis.axis, EVENT.jaxis.value);
                    break;

                case SDL_JOYBUTTONDOWN:
                    SDL_Log("Joystick %d button %d down\n",
                            EVENT.jbutton.which, EVENT.jbutton.button);
                    // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L52
                    // seek for joystick #0
                    if (EVENT.jbutton.which == 0) {
                        if (EVENT.jbutton.button == 0) {
                            // (A) button down
                        } else if (EVENT.jbutton.button == 10) {
                            // (+) button down
                            done = 1;
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // fill window bounds
        SDL_SetRenderDrawColor(renderer, 111, 111, 111, 255);
        SDL_GetWindowSize(window, &w, &h);
        SDL_Rect f = {0, 0, w, h};
        SDL_RenderFillRect(renderer, &f);

        draw_rects(renderer, x, 0);
        draw_rects(renderer, x, h - 64);

        SDL_RenderPresent(renderer);

        x++;
        if (x > w - 192) {
            x = 0;
        }
    }*/
    //SDL_Renderer *renderer, SDL_Surface* window_surface, TTF_Font *font, char *path

    Term_Services();
    return 0;
}
