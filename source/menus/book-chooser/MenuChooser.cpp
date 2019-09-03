extern "C" {
    #include "MenuChooser.h"
    #include "menu_book_reader.h"
    #include "SDL_helper.h"
    #include "common.h"
    #include "textures.h"
}

#include <switch.h>
#include <iostream>
#include <filesystem>
#include <bits/stdc++.h>

#include <SDL2/SDL_image.h>

using namespace std;
namespace fs = filesystem;

template <typename T> bool contains(std::list<T> & listOfElements, const T & element) {
	auto it = std::find(listOfElements.begin(), listOfElements.end(), element);
	return it != listOfElements.end();
}

extern TTF_Font *ARIAL, *ARIAL_35, *ARIAL_25, *ARIAL_15;

void Menu_StartChoosing() {
    int choosenIndex = 0;
    bool readingBook = false;
    list<string> allowedExtentions = {".pdf", ".epub", ".cbz", ".xps"};
    list<string> warnedExtentions = {".epub", ".cbz", ".xps"};

    string path = "/switch/eBookReader/books";

    // Count the amount of allowed files
    int amountOfFiles = 0;
    for (const auto & entry : fs::directory_iterator(path)) {
        string filename = entry.path().filename().string();
        string extention = filename.substr(filename.find_last_of("."));

        if (contains(allowedExtentions, extention)) {
            amountOfFiles++;
        }
    }

    bool isWarningOnScreen = false;
    int windowX, windowY;
    SDL_GetWindowSize(WINDOW, &windowX, &windowY);
    int warningWidth = 700;
    int warningHeight = 300;
    while(appletMainLoop()) {
        if (readingBook) {
            break;
        }

        SDL_ClearScreen(RENDERER, WHITE);
		SDL_RenderClear(RENDERER);

        hidScanInput();

        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) {
            break;
        }

        if (kDown & KEY_B) {
            isWarningOnScreen = false;
        }

        if (kDown & KEY_A) {
            int bookIndex = 0;
            for (const auto & entry : fs::directory_iterator(path)) {
                string filename = entry.path().filename().string();
                string extention = filename.substr(filename.find_last_of("."));

                if (contains(allowedExtentions, extention)) {
                    if (bookIndex == choosenIndex) {
                        if (contains(warnedExtentions, extention)) {
                            #ifdef EXPERIMENTAL
                                SDL_DrawImage(RENDERER, warning, 5, 10 + (40 * choosingIndex));
                            #endif
                            if (isWarningOnScreen) {
                                goto OPEN_BOOK;
                            } else {
                                isWarningOnScreen = true;
                            }
                        } else {
                            OPEN_BOOK:
                                string book = path + "/" + filename;
                                cout << "Opening book: " << book << endl;

                                Menu_OpenBook((char*) book.c_str());
                                readingBook = true;
                                break;
                        }
                    }

                    bookIndex++;
                }
            }
        }

        if (kDown & KEY_DUP) {
            if (choosenIndex != 0 && !isWarningOnScreen) choosenIndex--;
        }

        if (kDown & KEY_DDOWN) {
            if (choosenIndex < amountOfFiles-1 && !isWarningOnScreen) choosenIndex++;
        }

        int choosingIndex = 0;
        for (const auto & entry : fs::directory_iterator(path)) {
            string filename = entry.path().filename().string();
            string extention = filename.substr(filename.find_last_of("."));

            if (contains(allowedExtentions, extention)) {
                if (choosenIndex == choosingIndex) {
                    SDL_DrawRect(RENDERER, 15, 15 + (40 * choosingIndex), 1265, 40, SELECTOR_COLOUR_LIGHT);
                }

                #ifdef EXPERIMENTAL
                    if (contains(warnedExtentions, extention)) {
                        SDL_DrawImage(RENDERER, warning, 5, 10 + (40 * choosingIndex));
                    }
                #endif
                
                SDL_DrawText(RENDERER, ARIAL_25, 50, 20 + (40 * choosingIndex), BLACK, entry.path().filename().c_str());
                SDL_DrawText(RENDERER, ARIAL_25, windowX - 123, windowY - 35, BLACK, "\"+\"  -  Exit");

                if (isWarningOnScreen) {
                    SDL_DrawRect(RENDERER, 0, 0, 1280, 720, SDL_MakeColour(50, 50, 50, 150));

                    SDL_DrawRect(RENDERER, (windowX - warningWidth) / 2, (windowY - warningHeight) / 2, warningWidth, warningHeight, HINT_COLOUR_LIGHT);
                    SDL_DrawText(RENDERER, ARIAL_30, (windowX - warningWidth) / 2 + 15, (windowY - warningHeight) / 2 + 15, BLACK, "This file is not yet fully supported, and may");
                    SDL_DrawText(RENDERER, ARIAL_30, (windowX - warningWidth) / 2 + 15, (windowY - warningHeight) / 2 + 50, BLACK, "cause a system, or app crash.");
                    SDL_DrawText(RENDERER, ARIAL_20, (windowX - warningWidth) / 2 + warningWidth - 250, (windowY - warningHeight) / 2 + warningHeight - 30, BLACK, "\"A\" - Read");
                    SDL_DrawText(RENDERER, ARIAL_20, (windowX - warningWidth) / 2 + warningWidth - 125, (windowY - warningHeight) / 2 + warningHeight - 30, BLACK, "\"B\" - Cancel.");
                }

                choosingIndex++;
            }
        }

        SDL_RenderPresent(RENDERER);
    }
}