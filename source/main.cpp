#include <switch.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "fs.h"
#include "common.h"

#include "menu_book_reader.h"

using namespace std;

static void Term_Services(void) {
	
	TTF_CloseFont(Roboto_OSK);
	TTF_CloseFont(Roboto_small);
	TTF_CloseFont(Roboto);
	TTF_CloseFont(Roboto_large);
	TTF_Quit();

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	SDL_DestroyRenderer(RENDERER);
	SDL_FreeSurface(WINDOW_SURFACE);
	SDL_DestroyWindow(WINDOW);

	//#ifdef DEBUG
	socketExit();
	//#endif

	timeExit();
	SDL_Quit();
	romfsExit();
}

static void Init_Services(void) {
	romfsInit();
	// mandatory at least on switch, else gfx is not properly closed
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        Term_Services();
    }
	timeInitialize();

	/*#ifdef DEBUG
	socketInitializeDefault();*/
	nxlinkStdio();
	//#endif

	printf("Init Services");

	//SDL_CreateWindowAndRenderer(1280, 720, 0, &WINDOW, &RENDERER);

	WINDOW = SDL_CreateWindow("sdl2_gles2", 0, 0, 1920, 1080, 0);
    if (!WINDOW) {
        SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        Term_Services();
    }

	WINDOW_SURFACE = SDL_GetWindowSurface(WINDOW);

	RENDERER = SDL_CreateRenderer(WINDOW, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!RENDERER) {
        SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_Quit();
        Term_Services();
    }

	/*SDL_SetRenderDrawBlendMode(RENDERER, SDL_BLENDMODE_BLEND);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);*/

	TTF_Init();
	Roboto_large = TTF_OpenFont("romfs:/arial-unicode-ms.tff", 30);
	Roboto = TTF_OpenFont("romfs:/arial-unicode-ms.tff", 25);
	Roboto_small = TTF_OpenFont("romfs:/arial-unicode-ms.tff", 20);
	Roboto_OSK = TTF_OpenFont("romfs:/arial-unicode-ms.tff", 50);
	if (!Roboto_large || !Roboto || !Roboto_small || !Roboto_OSK)
		Term_Services();

	FS_RecursiveMakeDir("/switch/eBookReader/");
    FS_RecursiveMakeDir("/switch/eBookReader/books");
}

int main(int argc, char **argv) {
	//Init_Services();
	printf("AFTER INIT");

	/*if (setjmp(exitJmp)) {
		Term_Services();
		return 0;
	}

	//Menu_OpenBook("/switch/eBookReader/books/test.epub");
	Term_Services();*/
}