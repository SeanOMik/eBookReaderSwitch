extern "C" {
    #include "MenuChooser.h"
    #include "menu_book_reader.h"
    #include "SDL_helper.h"
    #include "common.h"
    #include "textures.h"
    #include "config.h"
}

#include <switch.h>
#include <iostream>
#include <filesystem>
#include <bits/stdc++.h>

#include <SDL2/SDL_image.h>

using namespace std;
namespace fs = filesystem;

template <typename T> bool contains(list<T> & listOfElements, const T & element) {
	auto it = find(listOfElements.begin(), listOfElements.end(), element);
	return it != listOfElements.end();
}

extern TTF_Font *ROBOTO_35, *ROBOTO_25, *ROBOTO_15;

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

    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    PadState pad;
    padInitializeDefault(&pad);

    while(appletMainLoop()) {
        if (readingBook) {
            break;
        }

        SDL_Color textColor = configDarkMode ? WHITE : BLACK;
        SDL_Color backColor = configDarkMode ? BACK_BLACK : BACK_WHITE;

        SDL_ClearScreen(RENDERER, backColor);
		SDL_RenderClear(RENDERER);

	padUpdate(&pad);

	u64 kDown = padGetButtonsDown(&pad);
	u64 kHeld = padGetButtons(&pad);
	u64 kUp = padGetButtonsUp(&pad);

        if (!isWarningOnScreen && kDown & HidNpadButton_Plus) {
            break;
        }

        if (kDown & HidNpadButton_B) {
            if (!isWarningOnScreen) {
                break;
            } else {
                isWarningOnScreen = false;
            }
        }

        if (kDown & HidNpadButton_A) {
            int bookIndex = 0;
            for (const auto & entry : fs::directory_iterator(path)) {
                string filename = entry.path().filename().string();
                string extention = filename.substr(filename.find_last_of("."));

                if (contains(allowedExtentions, extention)) {
                    if (bookIndex == choosenIndex) {
                        if (contains(warnedExtentions, extention)) {
                            /*#ifdef EXPERIMENTAL
                                SDL_DrawImage(RENDERER, warning, 5, 10 + (40 * choosingIndex));
                            #endif*/
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

        if (kDown & HidNpadButton_Up || kDown & HidNpadButton_StickRUp) {
            if (choosenIndex != 0 && !isWarningOnScreen) {
                choosenIndex--;
            } else if (choosenIndex == 0) {
                choosenIndex = amountOfFiles-1;
            }
        }

        if (kDown & HidNpadButton_Down || kDown & HidNpadButton_StickRDown) {
            if (choosenIndex == amountOfFiles-1) {
                choosenIndex = 0;
            } else if (choosenIndex < amountOfFiles-1 && !isWarningOnScreen) {
                choosenIndex++;
            }
        }

        if (kUp & HidNpadButton_Minus) {
            configDarkMode = !configDarkMode;
        }

        int exitWidth = 0;
        TTF_SizeText(ROBOTO_20, "Exit", &exitWidth, NULL);
        SDL_DrawButtonPrompt(RENDERER, button_b, ROBOTO_20, textColor, "Exit", windowX - exitWidth - 50, windowY - 10, 35, 35, 5, 0);

        int themeWidth = 0;
        TTF_SizeText(ROBOTO_20, "Switch Theme", &themeWidth, NULL);
        SDL_DrawButtonPrompt(RENDERER, button_minus, ROBOTO_20, textColor, "Switch Theme", windowX - themeWidth - 50, windowY - 40, 35, 35, 5, 0);

        int choosingIndex = 0;
        for (const auto & entry : fs::directory_iterator(path)) {
            string filename = entry.path().filename().string();
            string extention = filename.substr(filename.find_last_of("."));

            if (contains(allowedExtentions, extention)) {
                if (choosenIndex == choosingIndex) {
                    SDL_DrawRect(RENDERER, 15, 15 + (40 * choosingIndex), 1265, 40, configDarkMode ? SELECTOR_COLOUR_DARK : SELECTOR_COLOUR_LIGHT);
                }

                if (contains(warnedExtentions, extention)) {
                    SDL_DrawImage(RENDERER, warning, 25, 18 + (40 * choosingIndex));
                }
                
                SDL_DrawText(RENDERER, ROBOTO_25, 70, 20 + (40 * choosingIndex), textColor, entry.path().filename().c_str());

                if (isWarningOnScreen) {
                    if (!configDarkMode) { // Display a dimmed background if on light mode
                        SDL_DrawRect(RENDERER, 0, 0, 1280, 720, SDL_MakeColour(50, 50, 50, 150));
                    }

                    SDL_DrawRect(RENDERER, (windowX - warningWidth) / 2, (windowY - warningHeight) / 2, warningWidth, warningHeight, configDarkMode ? HINT_COLOUR_DARK : HINT_COLOUR_LIGHT);
                    SDL_DrawText(RENDERER, ROBOTO_30, (windowX - warningWidth) / 2 + 15, (windowY - warningHeight) / 2 + 15, textColor, "This file is not yet fully supported, and may");
                    SDL_DrawText(RENDERER, ROBOTO_30, (windowX - warningWidth) / 2 + 15, (windowY - warningHeight) / 2 + 50, textColor, "cause a system, or app crash.");
                    SDL_DrawText(RENDERER, ROBOTO_20, (windowX - warningWidth) / 2 + warningWidth - 250, (windowY - warningHeight) / 2 + warningHeight - 30, textColor, "\"A\" - Read");
                    SDL_DrawText(RENDERER, ROBOTO_20, (windowX - warningWidth) / 2 + warningWidth - 125, (windowY - warningHeight) / 2 + warningHeight - 30, textColor, "\"B\" - Cancel.");
                }

                choosingIndex++;
            }
        }

        SDL_RenderPresent(RENDERER);
    }
}
