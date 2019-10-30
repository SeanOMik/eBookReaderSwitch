extern "C" {
    #include "menu_book_reader.h"
    #include "MenuChooser.h"
    #include "common.h"
    #include "config.h"
    #include "SDL_helper.h"
}

#include <iostream>
#include "BookReader.hpp"

void Menu_OpenBook(char *path) {
    BookReader *reader = NULL;
    int result = 0;

    reader = new BookReader(path, &result);
    
    if(result < 0){
        std::cout << "Menu_OpenBook: document not loaded" << std::endl;
    }
    
    /*TouchInfo touchInfo;
    Touch_Init(&touchInfo);*/
    
    bool helpMenu = false;
    
    while(result >= 0 && appletMainLoop()) {
        reader->draw(helpMenu);
        
        hidScanInput();

        //Touch_Process(&touchInfo);

        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);
        
        if (!helpMenu && kDown & KEY_DLEFT) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait || (!hidGetHandheldMode())) {
                reader->previous_page(1);
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) && (hidGetHandheldMode())) {
                reader->zoom_out();
            }
        } else if (!helpMenu && kDown & KEY_DRIGHT) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait || (!hidGetHandheldMode())) {
                reader->next_page(1);
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) && (hidGetHandheldMode())) {
                reader->zoom_in();
            }
        }

        if (!helpMenu && kDown & KEY_R) {
            reader->next_page(10);
        } else if (!helpMenu && kDown & KEY_L) {
            reader->previous_page(10);
        }

        if (!helpMenu && ((kDown & KEY_DUP) || (kHeld & KEY_RSTICK_UP))) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait || (!hidGetHandheldMode())) {
                reader->zoom_in();
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) && (hidGetHandheldMode())) {
                reader->previous_page(1);
            }
        } else if (!helpMenu && ((kDown & KEY_DDOWN) || (kHeld & KEY_RSTICK_DOWN))) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait || (!hidGetHandheldMode())) {
                reader->zoom_out();
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) && (hidGetHandheldMode())) {
                reader->next_page(1);
            }
        }

        if (!helpMenu && kHeld & KEY_LSTICK_UP) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait || (!hidGetHandheldMode())) {
                reader->move_page_up();
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) && (hidGetHandheldMode())) {
                reader->move_page_left();
            }
        } else if (!helpMenu && kHeld & KEY_LSTICK_DOWN) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait || (!hidGetHandheldMode())) {
                reader->move_page_down();
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) && (hidGetHandheldMode())) {
                reader->move_page_right();
            }
        } else if (!helpMenu && kHeld & KEY_LSTICK_RIGHT) {
            if ((reader->currentPageLayout() == BookPageLayoutLandscape) && (hidGetHandheldMode())) {
                //reader->move_page_up();
                reader->move_page_down();
            }
        } else if (!helpMenu && kHeld & KEY_LSTICK_LEFT) {
            if ((reader->currentPageLayout() == BookPageLayoutLandscape) && (hidGetHandheldMode())) {
                //reader->move_page_down();
                reader->move_page_up();
            }
        }

        if (kDown & KEY_B) {
            if (helpMenu) {
                helpMenu = !helpMenu;
            } else {
                break;
            }
        }

        if (!helpMenu && kDown & KEY_X) {
            reader->permStatusBar = !reader->permStatusBar;
        }
            
        if (!helpMenu && kDown & KEY_LSTICK || kDown & KEY_RSTICK) {
            reader->reset_page();
        }
        
        if (!helpMenu && kDown & KEY_Y) {
            reader->switch_page_layout();
        }

        if (!helpMenu && kDown & KEY_MINUS) {
            configDarkMode = !configDarkMode;
            reader->previous_page(0);
        }

        if (kDown & KEY_PLUS) {
            helpMenu = !helpMenu;
        }
        
        /*if (touchInfo.state == TouchEnded && touchInfo.tapType != TapNone) {
            float tapRegion = 120;
            
            switch (reader->currentPageLayout()) {
                case BookPageLayoutPortrait:
                    if (tapped_inside(touchInfo, 0, 0, tapRegion, 720))
                        reader->previous_page(1);
                    else if (tapped_inside(touchInfo, 1280 - tapRegion, 0, 1280, 720))
                        reader->next_page(1);
                    break;
                case BookPageLayoutLandscape:
                    if (tapped_inside(touchInfo, 0, 0, 1280, tapRegion))
                        reader->previous_page(1);
                    else if (tapped_inside(touchInfo, 0, 720 - tapRegion, 1280, 720))
                        reader->next_page(1);
                    reader->reset_page();
                    break;
            }
        }*/
    }

    std::cout << "Exiting reader" << std::endl;
    std::cout << "Opening chooser" << std::endl;
    Menu_StartChoosing();
    delete reader;
}
