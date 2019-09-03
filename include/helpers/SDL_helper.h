#ifndef EBOOK_READER_SDL_HELPER_H
#define EBOOK_READER_SDL_HELPER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

static inline SDL_Color SDL_MakeColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_Color colour = {r, g, b, a};
	return colour;
}

#define WHITE                 SDL_MakeColour(255, 255, 255, 255)
#define BLACK                 SDL_MakeColour(0, 0, 0, 255)
#define LIGHT_GRAY            SDL_MakeColour(181, 181, 181, 255)
#define DARK_GRAY             SDL_MakeColour(148, 148, 148, 255)
#define BLACK_BG              SDL_MakeColour(48, 48, 48, 255)
#define STATUS_BAR_LIGHT      SDL_MakeColour(240, 43, 43, 255)
#define STATUS_BAR_DARK       SDL_MakeColour(163, 20, 20, 255)
#define MENU_BAR_LIGHT        SDL_MakeColour(240, 43, 43, 255)
#define MENU_BAR_DARK         SDL_MakeColour(163, 20, 20, 255)
#define TEXT_MIN_COLOUR_LIGHT SDL_MakeColour(32, 32, 32, 255)
#define SELECTOR_COLOUR_LIGHT SDL_MakeColour(220, 220, 220, 255)
#define SELECTOR_COLOUR_DARK  SDL_MakeColour(76, 76, 76, 255)
#define HINT_COLOUR_LIGHT	  SDL_MakeColour(210, 210, 210, 255)
#define HINT_COLOUR_DARK 	  SDL_MakeColour(70, 70, 70, 255)
#define TITLE_COLOUR          SDL_MakeColour(30, 136, 229, 255)
#define TITLE_COLOUR_DARK     SDL_MakeColour(0, 150, 136, 255)
#define TEXT_MIN_COLOUR_DARK  SDL_MakeColour(185, 185, 185, 255)
#define BAR_COLOUR            SDL_MakeColour(200, 200, 200, 255)

void SDL_ClearScreen(SDL_Renderer *renderer, SDL_Color colour);
void SDL_DrawRect(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Color colour);
void SDL_DrawCircle(SDL_Renderer *renderer, int x, int y, int r, SDL_Color colour);
void SDL_DrawText(SDL_Renderer *renderer, TTF_Font *font, int x, int y, SDL_Color colour, const char *text);
void SDL_DrawTextf(SDL_Renderer *renderer, TTF_Font *font, int x, int y, SDL_Color colour, const char* text, ...);
void SDL_LoadImage(SDL_Renderer *renderer, SDL_Texture **texture, char *path);
void SDL_LoadImageBuf(SDL_Renderer *renderer, SDL_Texture **texture, void *mem, int size);
void SDL_DrawImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);
void SDL_DrawImageScale(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);

#endif