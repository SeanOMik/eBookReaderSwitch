#include "textures.h"
#include "common.h"
#include "SDL_helper.h"

SDL_Texture *battery_20, *battery_20_charging, *battery_30, *battery_30_charging, *battery_50, *battery_50_charging, \
			*battery_60, *battery_60_charging, *battery_80, *battery_80_charging, *battery_90, *battery_90_charging, \
			*battery_full, *battery_full_charging, *battery_low, *battery_unknown, *error, *warning, *button_a, *button_b, \
			*button_x, *button_y, *button_dpad_up_down, *button_dpad_left_right, *button_lb, *button_rb, *button_lt, \
			*button_rt, *button_minus, *button_plus, *left_stick_up_down, *right_stick_up_down;

void Textures_Load(void) {
	// Battery images
	SDL_LoadImage(&battery_20, "romfs:/resources/images/battery/battery_20.png");
	SDL_LoadImage(&battery_20_charging, "romfs:/resources/images/battery/battery_20_charging.png");
	SDL_LoadImage(&battery_30, "romfs:/resources/images/battery/battery_30.png");
	SDL_LoadImage(&battery_30_charging, "romfs:/resources/images/battery/battery_30_charging.png");
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

	// Info images
	SDL_LoadImage(&error, "romfs:/resources/images/info/error.png");
	SDL_LoadImage(&warning, "romfs:/resources/images/info/warning.png");

	// Button images
	SDL_LoadImage(&button_a, "romfs:/resources/images/control/Switch_A.png");
	SDL_LoadImage(&button_b, "romfs:/resources/images/control/Switch_B.png");
	SDL_LoadImage(&button_x, "romfs:/resources/images/control/Switch_X.png");
	SDL_LoadImage(&button_y, "romfs:/resources/images/control/Switch_Y.png");
	SDL_LoadImage(&button_dpad_up_down, "romfs:/resources/images/control/Switch_Dpad_Up_down.png");
	SDL_LoadImage(&button_dpad_left_right, "romfs:/resources/images/control/Switch_Dpad_Left_right.png");
	SDL_LoadImage(&button_lb, "romfs:/resources/images/control/Switch_LB.png");
	SDL_LoadImage(&button_rb, "romfs:/resources/images/control/Switch_RB.png");
	SDL_LoadImage(&button_lt, "romfs:/resources/images/control/Switch_LT.png");
	SDL_LoadImage(&button_rt, "romfs:/resources/images/control/Switch_RT.png");
	SDL_LoadImage(&button_minus, "romfs:/resources/images/control/Switch_Minus.png");
	SDL_LoadImage(&button_plus, "romfs:/resources/images/control/Switch_Plus.png");
	SDL_LoadImage(&left_stick_up_down, "romfs:/resources/images/control/Switch_Left_Stick_up_down.png");
	SDL_LoadImage(&right_stick_up_down, "romfs:/resources/images/control/Switch_Right_Stick_up_down.png");
}

void Textures_Free(void) {
	// Button images
	SDL_DestroyTexture(button_a);
	SDL_DestroyTexture(button_b);
	SDL_DestroyTexture(button_x);
	SDL_DestroyTexture(button_y);
	SDL_DestroyTexture(button_dpad_up_down);
	SDL_DestroyTexture(button_dpad_left_right);
	SDL_DestroyTexture(button_lb);
	SDL_DestroyTexture(button_rb);
	SDL_DestroyTexture(button_lt);
	SDL_DestroyTexture(button_rt);
	SDL_DestroyTexture(button_minus);
	SDL_DestroyTexture(button_plus);
	SDL_DestroyTexture(left_stick_up_down);
	SDL_DestroyTexture(right_stick_up_down);

	// Info images
	SDL_DestroyTexture(warning);
	SDL_DestroyTexture(error);

	// Battery images
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