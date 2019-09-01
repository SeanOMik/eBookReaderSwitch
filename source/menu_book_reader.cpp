#include <iostream>

extern "C" {
    #include "menu_book_reader.h"
    #include "common.h"
    //#include "touch_helper.h"
}

#include "BookReader.hpp"

extern SDL_Renderer* RENDERER;
extern SDL_Window* WINDOW;
extern SDL_Surface* WINDOW_SURFACE;

void Menu_OpenBook(char *path) {
    BookReader *reader = new BookReader(RENDERER, path);
    
    /*TouchInfo touchInfo;
    Touch_Init(&touchInfo);*/
    
    while(appletMainLoop()) {
        reader->draw(WINDOW_SURFACE, ARIAL_UNICODE);
        
        hidScanInput();
        //Touch_Process(&touchInfo);
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

        if ((kDown & KEY_B) || (kDown & KEY_PLUS)) {
            std::cout << "B | PLUS" << std::endl;
            break;
        }
        
        if ((kDown & KEY_DLEFT) || (kDown & KEY_L)) {
            std::cout << "B | LEFT" << std::endl;
            reader->previous_page();
        }
            
        if ((kDown & KEY_DRIGHT) || (kDown & KEY_R)) {
            std::cout << "B | RIGHT" << std::endl;
            reader->next_page();
        }
            
        if (kDown & KEY_LSTICK) {
            std::cout << "B | LEFT STICK KEY" << std::endl;
            reader->reset_page();
        }
        
        if (kHeld & KEY_DUP) {
            std::cout << "B | UP" << std::endl;
            reader->zoom_in();
        }
        
        if (kHeld & KEY_DDOWN) {
            std::cout << "B | DOWN" << std::endl;
            reader->zoom_out();
        }
        
        if (kHeld & KEY_LSTICK_UP) {
            std::cout << "B | LEFT STICK UP" << std::endl;
            reader->move_page_up();
        }
        
        if (kHeld & KEY_LSTICK_DOWN) {
            std::cout << "B | LEFT STICK DOWN" << std::endl;
            reader->move_page_down();
        }
        
        if (kHeld & KEY_LSTICK_LEFT) {
            std::cout << "B | LEFT STICK LEFT" << std::endl;
            reader->move_page_left();
        }
        
        if (kHeld & KEY_LSTICK_RIGHT) {
            std::cout << "B | LEFT STICK RIGHT" << std::endl;
            reader->move_page_right();
        }
            
        /*if (touchInfo.state == TouchEnded && touchInfo.tapType != TapNone)
        {
            if (tapped_inside(touchInfo, 0, 0, 120, 720))
                reader->previous_page();
            else if (tapped_inside(touchInfo, 1160, 0, 1280, 720))
                reader->next_page();
        }*/
    }
    
    delete reader;
}
