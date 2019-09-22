#include "textures.h"
#include "common.h"
#include "SDL_helper.h"

SDL_Texture *battery_20, *battery_20_charging, *battery_30, *battery_30_charging, *battery_50, *battery_50_charging, \
			*battery_60, *battery_60_charging, *battery_80, *battery_80_charging, *battery_90, *battery_90_charging, \
			*battery_full, *battery_full_charging, *battery_low, *battery_unknown, *error, *warning, *button_a, *button_b, \
			*button_x, *button_y, *button_down, *button_up, *button_left, *button_right, *button_lb, *button_rb, *button_lt, \
			*button_rt, *button_minus, *button_plus, *button_capture, *button_home;

void Textures_Load(void) {
	SDL_LoadImage(&battery_20, "romfs:/resources/images/battery/battery_20.png");
	SDL_LoadImage(&battery_20_charging, "romfs:/resources/images/battery/battery_20_charging.png");
	SDL_LoadImage(&battery_30, "romfs:/resources/images/battery/battery_30.png");
	SDL_LoadImage(&battery_30_charging, "romfs:/resources/images/battery/battery/battery_30_charging.png");
	SDL_LoadImage(&battery_50, "romfs:/resources/images/battery/battery_50.png");
	SDL_LoadImage(&battery_50_charging, "romfs:/resources/images/battery/battery_50_charging.png");
	SDL_LoadImage(&battery_60, "romfs:/resources/images/battery/battery_60.png");
	SDL_LoadImage(&battery_60_charging, "romfs:/resources/images/battery/battery_60_charging.png");
	SDL_LoadImage(&battery_80, "romfs:/resources/images/battery/battery_80.png");
	SDL_LoadImage(&battery_80_charging, "romfs:/resources/images/battery/battery_80_charging.png");
	SDL_LoadImage(&battery_90, "romfs:/resources/images/battery/battery_90.png");
	SDL_LoadImage(&battery_90_charging, "romfs:/resources/images/battery/battery_90_charging.png");
	SDL_LoadImage(&battery_full, "romfs:/resources/images/battery/battery_full.png");
	SDL_LoadImage(&battery_full_charging, "romfs:/resources/images/battery/battery_full_charging.png");
	SDL_LoadImage(&battery_low, "romfs:/resources/images/battery/battery_low.png");
	SDL_LoadImage(&battery_unknown, "romfs:/resources/images/battery/battery_unknown.png");
	SDL_LoadImage(&error, "romfs:/resources/images/info/error.png");
	SDL_LoadImage(&warning, "romfs:/resources/images/info/warning.png");
}

void Textures_Free(void) {
	SDL_DestroyTexture(warning);
	SDL_DestroyTexture(error);
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