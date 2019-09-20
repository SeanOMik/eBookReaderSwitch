#include <time.h>
#include <switch.h>

#include "common.h"
#include "SDL_helper.h"
#include "status_bar.h"
#include "textures.h"

static char *Clock_GetCurrentTime(void) {
	static char buffer[10];

    time_t unixTime = time(NULL);
	struct tm* timeStruct = gmtime((const time_t *)&unixTime);
	int hours = (timeStruct->tm_hour);
	int minutes = timeStruct->tm_min;
	
	bool amOrPm = false;
	
	if (hours < 12)
		amOrPm = true;
	if (hours == 0)
		hours = 12;
	else if (hours > 12)
		hours = hours - 12;

	if ((hours >= 1) && (hours < 10))
		snprintf(buffer, 10, "%2i:%02i %s", hours, minutes, amOrPm ? "AM" : "PM");
	else
		snprintf(buffer, 10, "%2i:%02i %s", hours, minutes, amOrPm ? "AM" : "PM");

	return buffer;
}

static void StatusBar_GetBatteryStatus(int x, int y) {
	u32 percent = 0;
	ChargerType state;
	int width = 0;
	char buf[5];

	if (R_FAILED(psmGetChargerType(&state)))
		state = 0;
	
	if (R_SUCCEEDED(psmGetBatteryChargePercentage(&percent))) {
		if (percent < 20) {
			SDL_DrawImage(RENDERER, battery_low, x, 3);
		} else if ((percent >= 20) && (percent < 30)) {
			if (state != 0) {
				SDL_DrawImage(RENDERER, battery_20_charging, x, 3);
			} else {
				SDL_DrawImage(RENDERER, battery_20, x, 3);
			}
		} else if ((percent >= 30) && (percent < 50)) {
			if (state != 0) {
				SDL_DrawImage(RENDERER, battery_50_charging, x, 3);
			} else {
				SDL_DrawImage(RENDERER, battery_50, x, 3);
			}
		} else if ((percent >= 50) && (percent < 60)) {
			if (state != 0) {
				SDL_DrawImage(RENDERER, battery_50_charging, x, 3);
			} else {
				SDL_DrawImage(RENDERER, battery_50, x, 3);
			}
		} else if ((percent >= 60) && (percent < 80)) {
			if (state != 0) {
				SDL_DrawImage(RENDERER, battery_60_charging, x, 3);
			} else {
				SDL_DrawImage(RENDERER, battery_60, x, 3);
			}
		} else if ((percent >= 80) && (percent < 90)) {
			if (state != 0) {
				SDL_DrawImage(RENDERER, battery_80_charging, x, 3);
			} else {
				SDL_DrawImage(RENDERER, battery_80, x, 3);
			}
		} else if ((percent >= 90) && (percent < 100)) {
			if (state != 0) {
				SDL_DrawImage(RENDERER, battery_90_charging, x, 3);
			} else {
				SDL_DrawImage(RENDERER, battery_90, x, 3);
			}
		} else if (percent == 100) {
			if (state != 0) {
				SDL_DrawImage(RENDERER, battery_full_charging, x, 3);
			} else {
				SDL_DrawImage(RENDERER, battery_full, x, 3);
			}
		}

		snprintf(buf, 5, "%d%%", percent);
		TTF_SizeText(ARIAL_15, buf, &width, NULL);
		SDL_DrawText(RENDERER, ARIAL_15, (x - width - 10), y, WHITE, buf);
	} else {
		snprintf(buf, 5, "%d%%", percent);
		TTF_SizeText(ARIAL_15, buf, &width, NULL);
		SDL_DrawText(RENDERER, ARIAL_15, (x - width - 10), y, WHITE, buf);
		SDL_DrawImage(RENDERER, battery_unknown, x, 1);
	}
}

void StatusBar_DisplayTime(bool portriat) {
	int timeWidth = 0, timeHeight = 0;
	TTF_SizeText(ARIAL_25, Clock_GetCurrentTime(), &timeWidth, &timeHeight);
	int helpWidth, helpHeight;
	TTF_SizeText(ARIAL_20, "\"+\" - Help", &helpWidth, &helpHeight);

	#ifdef EXPERIMENTAL
		//StatusBar_GetBatteryStatus(1260 - width - 44, (40 - height) / 2);
	#endif
	if (portriat) {
		int timeX = (1280 - timeWidth) + timeHeight;
        int timeY = (720 - timeWidth) + 15;
        SDL_DrawRotatedText(RENDERER, ARIAL_25, (double) 90, timeX, timeY, WHITE, Clock_GetCurrentTime());
		
		int helpX = (1280 - helpWidth) + 21;
		int helpY = (720 - helpHeight) - (720 - timeY) - 75;
		SDL_DrawRotatedText(RENDERER, ARIAL_20, (double) 90, helpX, helpY, WHITE, "\"+\" - Help");

		//SDL_DrawRotatedText(RENDERER, ARIAL_25, (double) 90, 1270 - width, (720 - height), WHITE, Clock_GetCurrentTime());
	} else {
		SDL_DrawText(RENDERER, ARIAL_25, 1260 - timeWidth, (40 - timeHeight) / 2, WHITE, Clock_GetCurrentTime());

		SDL_DrawText(RENDERER, ARIAL_20, 1260 - helpWidth - timeWidth - 25, (40 - helpHeight) / 2, WHITE, "\"+\" - Help");
	} 
}