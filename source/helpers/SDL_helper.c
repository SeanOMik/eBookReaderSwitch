#include "common.h"
#include "SDL_helper.h"
#include <SDL2/SDL_image.h>

void SDL_ClearScreen(SDL_Renderer *renderer, SDL_Color colour) {
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderClear(renderer);
}

void SDL_DrawRect(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color colour) {
	SDL_Rect rect;
	rect.x = x; rect.y = y; rect.w = w; rect.h = h;
	SDL_SetRenderDrawColor(RENDERER, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(RENDERER, &rect);
}

void SDL_DrawCircle(SDL_Renderer *renderer, int x, int y, int r, SDL_Color colour) {
	filledCircleRGBA(renderer, x, y, r, colour.r, colour.g, colour.b, colour.a);
	return;
}

void SDL_DrawText(SDL_Renderer *renderer, TTF_Font *font, int x, int y, SDL_Color colour, const char *text) {
	SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text, colour, 1280);
	SDL_SetSurfaceAlphaMod(surface, colour.a);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	SDL_Rect position;
	position.x = x; position.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	SDL_RenderCopy(renderer, texture, NULL, &position);
	SDL_DestroyTexture(texture);
}

void SDL_DrawRotatedText(SDL_Renderer *renderer, TTF_Font *font, double rotation, int x, int y, SDL_Color colour, const char *text) {
	SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text, colour, 1280);
	SDL_SetSurfaceAlphaMod(surface, colour.a);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	SDL_Rect position;
	position.x = x; position.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	SDL_Point center = {position.w / 2, position.h / 2};
    SDL_Rect crop = {0, 0, &position.w, &position.h};

	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderCopyEx(RENDERER, texture, NULL, &position, rotation, NULL, SDL_FLIP_NONE);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_DestroyTexture(texture);
}

void SDL_DrawTextf(SDL_Renderer *renderer, TTF_Font *font, int x, int y, SDL_Color colour, const char* text, ...) {
	char buffer[256];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, 256, text, args);
	SDL_DrawText(renderer, font, x, y, colour, buffer);
	va_end(args);
}

void SDL_LoadImage(SDL_Texture **texture, char *path) {
	SDL_Surface *image = NULL;

	image = IMG_Load(path);
	if (!image) {
		//DEBUG_LOG("IMG_Load failed: %s\n", IMG_GetError());
		printf("IMG_Load failed: %s\n", IMG_GetError());
		
		return;
	}
	
	SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA8888, 0);
	*texture = SDL_CreateTextureFromSurface(RENDERER, image);
	SDL_FreeSurface(image);
	image = NULL;
}

void SDL_DrawImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y) {
	SDL_Rect position;
	position.x = x; position.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	SDL_RenderCopy(renderer, texture, NULL, &position);
}

void SDL_DrawImageScale(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h) {
	SDL_Rect position;
	position.x = x; position.y = y; position.w = w; position.h = h;
	SDL_RenderCopy(renderer, texture, NULL, &position);
}