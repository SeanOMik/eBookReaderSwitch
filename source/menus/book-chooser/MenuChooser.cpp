extern "C" {
    #include "MenuChooser.h"
    #include "menu_book_reader.h"
    #include "common.h"
    #include "SDL_helper.h"
}

#include <switch.h>
#include <iostream>
/*#include <dirent.h>
#include <sys/types.h>*/
#include <filesystem>

using namespace std;
namespace fs = filesystem;
//using namespace std;

//extern bool readingBook;

void Menu_StartChoosing() {
    int choosenIndex = 0;
    bool readingBook = false;

    string path = "/switch/eBookReader/books";
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

        if (kDown & KEY_A) {
            int bookIndex = 0;
            for (const auto & entry : fs::directory_iterator(path)) {
                string filename = entry.path().filename().string();
                string extention = filename.substr(filename.length() - 3);
                if (extention == "pdf") {
                    if (bookIndex == choosenIndex) {
                        char* book = (char *) entry.path().string().c_str();
                        Menu_OpenBook(book);
                        readingBook = true;
                        break;
                    }

                    choosenIndex++;
                }
            }
        }

        if (kDown & KEY_DUP) {
            if (choosenIndex != 0) choosenIndex--;
        }

        if (kDown & KEY_DDOWN) {
            choosenIndex++;
        }

        int space_index = 0;
        for (const auto & entry : fs::directory_iterator(path)) {
            string filename = entry.path().filename().string();
            string extention = filename.substr(filename.length() - 3);
            if (extention == "pdf") {
                if (choosenIndex == space_index) {
                    SDL_DrawRect(RENDERER, 15, 20 + (40 * space_index), 1265, 40, SELECTOR_COLOUR_LIGHT);
                }

                SDL_DrawText(RENDERER, ARIAL, 20, 20 + (40 * space_index), BLACK, entry.path().filename().c_str());

                space_index++;
            }
        }

        SDL_RenderPresent(RENDERER);
    }
}


/*void list_dir(const char *path) {
    struct dirent *entry;
    DIR *dir = opendir(path);
   
    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        entry->
        //cout << entry->d_name << endl;
    }
    closedir(dir);
}*/