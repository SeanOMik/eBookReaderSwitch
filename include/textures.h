#ifndef EBOOK_READER_TEXTURES_H
#define EBOOK_READER_TEXTURES_H

#include <SDL2/SDL.h>

extern SDL_Texture *battery_20, *battery_20_charging, *battery_30, *battery_30_charging, *battery_50, *battery_50_charging, \
			*battery_60, *battery_60_charging, *battery_80, *battery_80_charging, *battery_90, *battery_90_charging, \
			*battery_full, *battery_full_charging, *battery_low, *battery_unknown, *error, *warning;

void Textures_Load(void);
void Textures_Free(void);

#endif