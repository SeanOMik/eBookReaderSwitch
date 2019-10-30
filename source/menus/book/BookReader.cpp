#include "BookReader.hpp"
#include "PageLayout.hpp"
#include "LandscapePageLayout.hpp"
#include <algorithm>
#include <iostream>
#include <libconfig.h>

extern "C"  {
    #include "SDL_helper.h"
    #include "status_bar.h"
    #include "config.h"
    #include "textures.h"
    #include "common.h"
}

fz_context *ctx = NULL;
int windowX, windowY;
config_t *config = NULL;
char* configFile = "/switch/eBookReader/saved_pages.cfg";

static int load_last_page(const char *book_name)  {
    if (!config) {
        config = (config_t *)malloc(sizeof(config_t));
        config_init(config);
        config_read_file(config, configFile);
    }
    
    config_setting_t *setting = config_setting_get_member(config_root_setting(config), book_name);
    
    if (setting) {
        return config_setting_get_int(setting);
    }

    return 0;
}

static void save_last_page(const char *book_name, int current_page) {
    config_setting_t *setting = config_setting_get_member(config_root_setting(config), book_name);
    
    if (!setting) {
        setting = config_setting_add(config_root_setting(config), book_name, CONFIG_TYPE_INT);
    }
    
    if (setting) {
        config_setting_set_int(setting, current_page);
        config_write_file(config, configFile);
    }
}

BookReader::BookReader(const char *path, int* result) {
    if (ctx == NULL) {
        ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
        fz_register_document_handlers(ctx);
    }

    SDL_GetWindowSize(WINDOW, &windowX, &windowY);
    
    book_name = std::string(path).substr(std::string(path).find_last_of("/\\") + 1);
    
    std::string invalid_chars = " :/?#[]@!$&'()*+,;=.";
    for (char& c: invalid_chars) {
        book_name.erase(std::remove(book_name.begin(), book_name.end(), c), book_name.end());
    }
    
    fz_try(ctx)	{
        std::cout << "fz_open_document" << std::endl;
        doc = fz_open_document(ctx, path);

        if (!doc)
        {
            std::cout << "Error opening file!" << std::endl;
            *result = -1;
            return;
        }
        
        std::cout << "doc opened ok ?!" << std::endl;
        
        int current_page = load_last_page(book_name.c_str());
        //int current_page = 0;

        std::cout << "current_page = " << current_page << std::endl;

        switch_current_page_layout(_currentPageLayout, current_page);

        if (current_page > 0) {
            show_status_bar();
        }
    }
    fz_catch(ctx){
        std::cout << "fz_catch reached, closing gracefully" << std::endl;
        *result = -2;
        return;
    }
}

BookReader::~BookReader() {
    fz_drop_document(ctx, doc);
    
    delete layout;
}

void BookReader::previous_page(int n) {
    layout->previous_page(n);
    show_status_bar();
    save_last_page(book_name.c_str(), layout->current_page());
}

void BookReader::next_page(int n) {
    layout->next_page(n);
    show_status_bar();
    save_last_page(book_name.c_str(), layout->current_page());
}

void BookReader::zoom_in() {
    layout->zoom_in();
    show_status_bar();
}

void BookReader::zoom_out() {
    layout->zoom_out();
    show_status_bar();
}

void BookReader::move_page_up() {
    layout->move_up();
}

void BookReader::move_page_down() {
    layout->move_down();
}

void BookReader::move_page_left() {
    layout->move_left();
}

void BookReader::move_page_right() {
    layout->move_right();
}

void BookReader::reset_page() {
    layout->reset();
    show_status_bar();
}

void BookReader::switch_page_layout() {
    switch (_currentPageLayout) {
        case BookPageLayoutPortrait:
            switch_current_page_layout(BookPageLayoutLandscape, 0);
            break;
        case BookPageLayoutLandscape:
            switch_current_page_layout(BookPageLayoutPortrait, 0);
            break;
    }
}

void BookReader::draw(bool drawHelp) {
    //std::cout << "BookReader::draw" << std::endl;
    if (configDarkMode == true) {
        SDL_ClearScreen(RENDERER, BLACK);
    } else {
        SDL_ClearScreen(RENDERER, WHITE);
    }

    SDL_RenderClear(RENDERER);
    
    layout->draw_page();
    
    if (drawHelp) { // Help menu
        int helpWidth = 680;
        int helpHeight = 365;
        helpHeight -= 38; // Removed due to removing the skip forward page button prompt.

        if (!configDarkMode) { // Display a dimmed background if on light mode
            SDL_DrawRect(RENDERER, 0, 0, 1280, 720, SDL_MakeColour(50, 50, 50, 150));
        }

        SDL_DrawRect(RENDERER, (windowX - helpWidth) / 2, (windowY - helpHeight) / 2, helpWidth, helpHeight, configDarkMode ? HINT_COLOUR_DARK : HINT_COLOUR_LIGHT);

        int textX = (windowX - helpWidth) / 2 + 20;
        int textY = (windowY - helpHeight) / 2 + 87;
        SDL_Color textColor = configDarkMode ? WHITE : BLACK;
        SDL_DrawText(RENDERER, ROBOTO_30, textX, (windowY - helpHeight) / 2 + 10, textColor, "Help Menu:");

        SDL_DrawButtonPrompt(RENDERER, button_b,               ROBOTO_25, textColor, "Stop reading / Close help menu.", textX, textY,          35, 35, 5, 0);
        SDL_DrawButtonPrompt(RENDERER, button_minus,           ROBOTO_25, textColor, "Switch to dark/light theme.",     textX, textY + 38,     35, 35, 5, 0);
        SDL_DrawButtonPrompt(RENDERER, right_stick_up_down,    ROBOTO_25, textColor, "Zoom in/out.",                    textX, textY + 38 * 2, 35, 35, 5, 0);
        SDL_DrawButtonPrompt(RENDERER, left_stick_up_down,     ROBOTO_25, textColor, "Page up/down.",                   textX, textY + 38 * 3, 35, 35, 5, 0);
        SDL_DrawButtonPrompt(RENDERER, button_y,               ROBOTO_25, textColor, "Rotate page.",                    textX, textY + 38 * 4, 35, 35, 5, 0);
        SDL_DrawButtonPrompt(RENDERER, button_x,               ROBOTO_25, textColor, "Keep status bar on.",             textX, textY + 38 * 5, 35, 35, 5, 0);
        SDL_DrawButtonPrompt(RENDERER, button_dpad_left_right, ROBOTO_25, textColor, "Next/previous page.",             textX, textY + 38 * 6, 35, 35, 5, 0);
        //SDL_DrawButtonPrompt(RENDERER, button_dpad_up_down,    ROBOTO_25, textColor, "Skip forward/backward 10 pages.", textX, textY + 38 * 7, 35, 35, 5, 0);
    }

    if (permStatusBar || --status_bar_visible_counter > 0)  {
        char *title = layout->info();
        
        int title_width = 0, title_height = 0;
        TTF_SizeText(ROBOTO_15, title, &title_width, &title_height);
        
        SDL_Color color = configDarkMode ? STATUS_BAR_DARK : STATUS_BAR_LIGHT;
        
        if (_currentPageLayout == BookPageLayoutPortrait) {
            SDL_DrawRect(RENDERER, 0, 0, 1280, 45, SDL_MakeColour(color.r, color.g, color.b , 180));
            SDL_DrawText(RENDERER, ROBOTO_25, (1280 - title_width) / 2, (40 - title_height) / 2, WHITE, title);
            
            StatusBar_DisplayTime(false);
        } else if (_currentPageLayout == BookPageLayoutLandscape) {
            SDL_DrawRect(RENDERER, 1280 - 45, 0, 45, 720, SDL_MakeColour(color.r, color.g, color.b , 180));
            int x = (1280 - title_width) - ((40 - title_height) / 2);
            int y = (720 - title_height) / 2;
            SDL_DrawRotatedText(RENDERER, ROBOTO_25, (double) 90, x, y, WHITE, title);

            StatusBar_DisplayTime(true);
        }
    }
    
    
    SDL_RenderPresent(RENDERER);
}

void BookReader::show_status_bar() {
    status_bar_visible_counter = 200;
}

void BookReader::switch_current_page_layout(BookPageLayout bookPageLayout, int current_page) {
    std::cout << "enter switch_current_page_layout " << std::endl;

    if (layout) {
        current_page = layout->current_page();
        delete layout;
        layout = NULL;
    }
    
    _currentPageLayout = bookPageLayout;
    
    switch (bookPageLayout) {
        case BookPageLayoutPortrait:
            layout = new PageLayout(doc, current_page);
            break;
        case BookPageLayoutLandscape:
            layout = new LandscapePageLayout(doc, current_page);
            break;
    }

    std::cout << "exit switch_current_page_layout " << std::endl;
}
