extern "C" {
    #include "MenuChooser.h"
    #include "common.h"
    #include "SDL_helper.h"
}

#include <switch.h>
#include <iostream>
#include <dirent.h>
#include <sys/types.h>

//using namespace std;

void Menu_StartChoosing() {
    int choosen_index = 0;

    struct dirent *entry;
    DIR *dir = opendir("/switch/eBookReader/books");
    
    if (dir == NULL) {
        return;
    }

    while(appletMainLoop()) {
        SDL_ClearScreen(RENDERER, WHITE);
		SDL_RenderClear(RENDERER);

        int space_index = 0;
        while ((entry = readdir(dir)) != NULL) {
            SDL_DrawText(RENDERER, ARIAL_UNICODE, 20, 20 + (30 * space_index), BLACK, entry->d_name);
            space_index++;
            //cout << entry->d_name << endl;
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