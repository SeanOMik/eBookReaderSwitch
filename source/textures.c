#include "textures.h"
#include "common.h"
#include "SDL_helper.h"

SDL_Texture *battery_20, *battery_20_charging, *battery_30, *battery_30_charging, *battery_50, *battery_50_charging, \
			*battery_60, *battery_60_charging, *battery_80, *battery_80_charging, *battery_90, *battery_90_charging, \
			*battery_full, *battery_full_charging, *battery_low, *battery_unknown, *error, *warning;

void Textures_Load(void) {
	/*SDL_LoadImage(RENDERER, &battery_20, "romfs:/resources/images/battery_20.png");
	SDL_LoadImage(RENDERER, &battery_20_charging, "romfs:/resources/images/battery_20_charging.png");
	SDL_LoadImage(RENDERER, &battery_30, "romfs:/resources/images/battery_30.png");
	SDL_LoadImage(RENDERER, &battery_30_charging, "romfs:/resources/images/battery_30_charging.png");
	SDL_LoadImage(RENDERER, &battery_50, "romfs:/resources/images/battery_50.png");
	SDL_LoadImage(RENDERER, &battery_50_charging, "romfs:/resources/images/battery_50_charging.png");
	SDL_LoadImage(RENDERER, &battery_60, "romfs:/resources/images/battery_60.png");
	SDL_LoadImage(RENDERER, &battery_60_charging, "romfs:/resources/images/battery_60_charging.png");
	SDL_LoadImage(RENDERER, &battery_80, "romfs:/resources/images/battery_80.png");
	SDL_LoadImage(RENDERER, &battery_80_charging, "romfs:/resources/images/battery_80_charging.png");
	SDL_LoadImage(RENDERER, &battery_90, "romfs:/resources/images/battery_90.png");
	SDL_LoadImage(RENDERER, &battery_90_charging, "romfs:/resources/images/battery_90_charging.png");
	SDL_LoadImage(RENDERER, &battery_full, "romfs:/resources/images/battery_full.png");
	SDL_LoadImage(RENDERER, &battery_full_charging, "romfs:/resources/images/battery_full_charging.png");
	SDL_LoadImage(RENDERER, &battery_low, "romfs:/resources/images/battery_low.png");
	SDL_LoadImage(RENDERER, &battery_unknown, "romfs:/resources/images/battery_unknown.png");*/
	//SDL_LoadImage(RENDERER, &error, "romfs:/resources/images/error.png");

	SDL_Surface *imageSurface = IMG_Load("romfs:/resources/images/warning.png");

	if (imageSurface) {
		warning = SDL_CreateTextureFromSurface(RENDERER, imageSurface);
		if (warning == NULL) {
			fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
			exit(1);
		}

		printf("Loaded \"romfs:/resources/images/warning.png\"\n");
	} else {
		printf("Failed to load image: \"romfs:/resources/images/warning.png\"\n");
	}
	/*if (imageSurface) {
		Uint32 colorkey = SDL_MapRGB(imageSurface->format, 0, 0, 0);
		SDL_SetColorKey(imageSurface, SDL_TRUE, colorkey);
		warning = SDL_CreateTextureFromSurface(RENDERER, imageSurface);
	} else {
		printf("Failed to load image: %c", "romfs:/resources/images/warning.png");
	}

	SDL_FreeSurface(imageSurface);*/
	//SDL_LoadImage(RENDERER, &warning, "romfs:/resources/images/warning.png");
}

void Textures_Free(void) {
	SDL_DestroyTexture(warning);
	//SDL_DestroyTexture(error);
	/*SDL_DestroyTexture(battery_unknown);
	SDL_DestroyTexture(battery_low);
	SDL_DestroyTexture(battery_full_charging);
	SDL_DestroyTexture(battery_full);
	SDL_DestroyTexture(battery_90_charging);
	SDL_DestroyTexture(battery_80_charging);
	SDL_DestroyTexture(battery_80);
	SDL_DestroyTexture(battery_60_charging);
	SDL_DestroyTexture(battery_60);
	SDL_DestroyTexture(battery_50_charging);
	SDL_DestroyTexture(battery_50);
	SDL_DestroyTexture(battery_30_charging);
	SDL_DestroyTexture(battery_30);
	SDL_DestroyTexture(battery_20_charging);
	SDL_DestroyTexture(battery_20);*/
}