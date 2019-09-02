#include "textures.h"
#include "common.h"
#include "SDL_helper.h"

void Textures_Load(void) {
	SDL_LoadImage(RENDERER, &battery_20, "romfs:/battery_20.png");
	SDL_LoadImage(RENDERER, &battery_20_charging, "romfs:/battery_20_charging.png");
	SDL_LoadImage(RENDERER, &battery_30, "romfs:/battery_30.png");
	SDL_LoadImage(RENDERER, &battery_30_charging, "romfs:/battery_30_charging.png");
	SDL_LoadImage(RENDERER, &battery_50, "romfs:/battery_50.png");
	SDL_LoadImage(RENDERER, &battery_50_charging, "romfs:/battery_50_charging.png");
	SDL_LoadImage(RENDERER, &battery_60, "romfs:/battery_60.png");
	SDL_LoadImage(RENDERER, &battery_60_charging, "romfs:/battery_60_charging.png");
	SDL_LoadImage(RENDERER, &battery_80, "romfs:/battery_80.png");
	SDL_LoadImage(RENDERER, &battery_80_charging, "romfs:/battery_80_charging.png");
	SDL_LoadImage(RENDERER, &battery_90, "romfs:/battery_90.png");
	SDL_LoadImage(RENDERER, &battery_90_charging, "romfs:/battery_90_charging.png");
	SDL_LoadImage(RENDERER, &battery_full, "romfs:/battery_full.png");
	SDL_LoadImage(RENDERER, &battery_full_charging, "romfs:/battery_full_charging.png");
	SDL_LoadImage(RENDERER, &battery_low, "romfs:/battery_low.png");
	SDL_LoadImage(RENDERER, &battery_unknown, "romfs:/battery_unknown.png");
}

void Textures_Free(void) {
	SDL_DestroyTexture(battery_unknown);
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
	SDL_DestroyTexture(battery_20);
}