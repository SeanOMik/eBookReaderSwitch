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
    hidInitializeTouchScreen();

    s32 prev_touchcount=0;
    bool helpMenu = false;
    
    // Configure our supported input layout: a single player with standard controller syles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    // Initialize the default gamepad (which reads handheld mode inputs as well as the first connected controller)
    PadState pad;
    padInitializeDefault(&pad);
    //Touch_Process(&touchInfo);

    while(result >= 0 && appletMainLoop()) {
        reader->draw(helpMenu);
        
	padUpdate(&pad);

	u64 kDown = padGetButtonsDown(&pad);
	u64 kHeld = padGetButtons(&pad);	
	u64 kUp = padGetButtonsUp(&pad);

	HidTouchScreenState state={0};
	
	if(hidGetTouchScreenStates(&state, 1)) {
		if(state.count != prev_touchcount) {
			prev_touchcount = state.count;
		} 
	}

	for(s32 i=0; i<state.count; i++) {
		if (state.touches[i].x > 1000 && (state.touches[i].y > 200 && state.touches[i].y < 500))
			if (reader->currentPageLayout() == BookPageLayoutPortrait)
				reader->next_page(1);
			else if (reader->currentPageLayout() == BookPageLayoutLandscape)
				reader->zoom_in();

		if (state.touches[i].x < 280 && (state.touches[i].y > 200 && state.touches[i].y < 500))
			if (reader->currentPageLayout() == BookPageLayoutPortrait)
				reader->previous_page(1);
			else if (reader->currentPageLayout() == BookPageLayoutLandscape)
				reader->zoom_out();

		if (state.touches[i].y < 200)
			if (reader->currentPageLayout() == BookPageLayoutPortrait)
				reader->zoom_in();
			else if (reader->currentPageLayout() == BookPageLayoutLandscape)
				reader->previous_page(1);

		if (state.touches[i].y > 500)
			if (reader->currentPageLayout() == BookPageLayoutPortrait)
				reader->zoom_out();
			else if (reader->currentPageLayout() == BookPageLayoutLandscape)
				reader->next_page(1);
	}

        if (!helpMenu && kDown & HidNpadButton_Left) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait ) {
                reader->previous_page(1);
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) ) {
                reader->zoom_out();
            }
        } else if (!helpMenu && kDown & HidNpadButton_Right) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait ) {
                reader->next_page(1);
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) ) {
                reader->zoom_in();
            }
        }

        if (!helpMenu && kDown & HidNpadButton_R) {
            reader->next_page(10);
        } else if (!helpMenu && kDown & HidNpadButton_L) {
            reader->previous_page(10);
        }

        if (!helpMenu && ((kDown & HidNpadButton_Up) || (kHeld & HidNpadButton_StickRUp))) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait ) {
                reader->zoom_in();
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) ) {
                reader->previous_page(1);
            }
        } else if (!helpMenu && ((kDown & HidNpadButton_Down) || (kHeld & HidNpadButton_StickRDown))) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait ) {
                reader->zoom_out();
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) ) {
                reader->next_page(1);
            }
        }

        if (!helpMenu && kHeld & HidNpadButton_StickLUp) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait ) {
                reader->move_page_up();
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) ) {
                reader->move_page_right();
            }
        } else if (!helpMenu && kHeld & HidNpadButton_StickLDown) {
            if (reader->currentPageLayout() == BookPageLayoutPortrait ) {
                reader->move_page_down();
            } else if ((reader->currentPageLayout() == BookPageLayoutLandscape) ) {
                reader->move_page_left();
            }
        } else if (!helpMenu && kHeld & HidNpadButton_StickLRight) {
            if ((reader->currentPageLayout() == BookPageLayoutLandscape) ) {
                reader->move_page_down();
            }
        } else if (!helpMenu && kHeld & HidNpadButton_StickLLeft) {
            if ((reader->currentPageLayout() == BookPageLayoutLandscape) ) {
                reader->move_page_up();
            }
        }

	if (!helpMenu && kDown & HidNpadButton_LeftSR)
		reader->next_page(10);
	else if (!helpMenu && kDown & HidNpadButton_LeftSL)
		reader->previous_page(10);

        if (kUp & HidNpadButton_B) {
            if (helpMenu) {
                helpMenu = !helpMenu;
            } else {
                break;
            }
        }

        if (!helpMenu && kDown & HidNpadButton_X) {
            reader->permStatusBar = !reader->permStatusBar;
        }
            
        if ((!helpMenu && kDown & HidNpadButton_StickL) || kDown & HidNpadButton_StickR) {
            reader->reset_page();
        }
        
        if (!helpMenu && kDown & HidNpadButton_Y) {
            reader->switch_page_layout();
        }

        if (!helpMenu && kUp & HidNpadButton_Minus) {
            configDarkMode = !configDarkMode;
            reader->previous_page(0);
        }

        if (kDown & HidNpadButton_Plus) {
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
    // consoleExit(NULL);
}
