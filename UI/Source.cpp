#define NOMINMAX

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <filesystem>
#include "UI.h"

int main(int arhc, char** argv) {
    if (!init() || TTF_Init() < 0) {
        quit();
        system("pause");
        return 1;
    }
    
    std::string start_path = "Plugin/";
    std::vector<std::string> plugins_path;

    for (const auto& entry : std::filesystem::directory_iterator(start_path)) {
        std::string str = entry.path().string();
        if (str[str.size() - 3] == 'd' && str[str.size() - 2] == 'l' && str[str.size() - 1] == 'l') {
            plugins_path.push_back(str);
        }
    }

    MainWindow wind_main(&plugins_path);
       
    while(true) {
        SDL_RenderClear(ren);
        wind_main.Show();
        SDL_Event event;

        if (SDL_PollEvent(&event)) {
            eve = true;
            wind_main.UpdateEvent(&event);
        }
        wind_main.Update();
        SDL_RenderPresent(ren);
    }
   
    quit();
    return 0;
}