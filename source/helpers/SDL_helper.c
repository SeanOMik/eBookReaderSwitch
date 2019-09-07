#include "common.h"
#include "SDL_helper.h"

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
    SDL_Rect crop = {0, 0, &position.w, &position.h}; // the crop is what part of the image we want to display.

	SDL_SetRenderTarget(renderer, texture);
	//SDL_RenderCopyEx(RENDERER, texture, &crop, &position, rotation, &center, SDL_FLIP_NONE);
	SDL_RenderCopyEx(RENDERER, texture, NULL, &position, rotation, NULL, SDL_FLIP_NONE);
	SDL_SetRenderTarget(renderer, NULL);
	/*SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	SDL_RenderCopy(renderer, texture, NULL, &position);*/
	SDL_DestroyTexture(texture);
}

void SDL_InvertSurfaceColor(SDL_Surface *surface) {
	for(int x = 0; x < (*surface).w; x++) {
		for(int y = 0; y < (*surface).h; y++) {
			int r, g, b, a;
			Uint32 pixel = SDL_GetPixel32(&surface, x, y);
			SDL_GetRGBA(pixel, SDL_GetWindowPixelFormat(&WINDOW), &r, &g, &b, &a);
			SDL_Color color = SDL_MakeColour(255 - r, 255 - g, 255 - b, a);
			SDL_PutPixel32(&surface, x, y, pixel);
		}
	}
}

Uint32 SDL_GetPixel32(SDL_Surface *surface, int x, int y) {
	//Lock the surface.
	if(SDL_MUSTLOCK(surface)) {
		SDL_LockSurface(surface);
	}

    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];

	//Unlock when we are done.
	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}

void SDL_PutPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	//Lock the surface.
	if(SDL_MUSTLOCK(surface)) {
		SDL_LockSurface(surface);
	}

    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;

	//Unlock when we are done.
	if(SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
}

void SDL_DrawTextf(SDL_Renderer *renderer, TTF_Font *font, int x, int y, SDL_Color colour, const char* text, ...) {
	char buffer[256];
	va_list args;
	va_start(args, text);
	vsnprintf(buffer, 256, text, args);
	SDL_DrawText(renderer, font, x, y, colour, buffer);
	va_end(args);
}

void SDL_LoadImage(SDL_Renderer *renderer, SDL_Texture **texture, char *path) {
	SDL_Surface *imageSurface = IMG_Load(path);

	if (imageSurface) {
		Uint32 colorkey = SDL_MapRGB(imageSurface->format, 0, 0, 0);
		SDL_SetColorKey(imageSurface, SDL_TRUE, colorkey);
		*texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	} else {
		printf("Failed to load image: %s", path);
	}

	SDL_FreeSurface(imageSurface);
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