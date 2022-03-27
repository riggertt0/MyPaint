#pragma once
#include "ColorRGB.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 480;

const int TANK_WIDTH = 640;
const int TANK_HEIGHT = 480;

const int X_START_WINDOW = 448;
const int Y_START_WINDOW = 300;

const int INT_VALUE_0 = 48;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
bool eve = false;

bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Can't init SDL: %p\n", SDL_GetError());
        ok = false;
    }

    win = SDL_CreateWindow("Graphics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
    if (win == NULL) {
        printf("Can't create window: %p\n", SDL_GetError());
        ok = false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == NULL) {
        printf("Can't create renderer: %p", SDL_GetError());
        ok = false;
    }
    return ok;
}


void quit() {
    SDL_DestroyWindow(win);
    win = NULL;

    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_Quit();
}

void SetColor(ColorRGB color) {
    SDL_SetRenderDrawColor(ren, (int)(color.GetR() * 255), (int)(color.GetG() * 255), (int)(color.GetB() * 255), 0xFF);
}

void ClearAll() {
    SetColor({ 0,0,0 });
    //SDL_RenderClear(ren);
    SDL_Rect tank_rec;
    tank_rec.x = 0;
    tank_rec.y = 0;
    tank_rec.w = TANK_WIDTH;
    tank_rec.h = TANK_HEIGHT;
    SDL_RenderFillRect(ren, &tank_rec);
}

void ShowRect(int x, int y, int len, int hei) {
    SDL_Rect graph_rec;
    graph_rec.x = x;
    graph_rec.y = y;
    graph_rec.w = len;
    graph_rec.h = hei;
    SDL_RenderDrawRect(ren, &graph_rec);
}

void ShowDottedRect(int x, int y, int len, int hei, int step) {
    if (step > 5) {
        SDL_RenderDrawLine(ren, x, y, x + step - 5, y);
        SDL_RenderDrawLine(ren, x, y + hei, x + step - 5, y + hei);
        SDL_RenderDrawLine(ren, x, y, x, y + step - 5);
        SDL_RenderDrawLine(ren, x + len, y, x + len, y + step - 5);
    }
    for (int ind_x = x + step; ind_x <= x + len; ind_x += 10) {
        if(ind_x + 5 > x + len)
            SDL_RenderDrawLine(ren, ind_x, y, x + len, y);
        else
            SDL_RenderDrawLine(ren, ind_x, y, ind_x + 5, y);
    }
    for (int ind_y = y + step; ind_y <= y + hei; ind_y += 10) {
        if (ind_y + 5 > y + hei)
            SDL_RenderDrawLine(ren, x, ind_y, x, y + hei);
        else
            SDL_RenderDrawLine(ren, x, ind_y, x, ind_y + 5);
    }
    for (int ind_x = x + step; ind_x <= x + len; ind_x += 10) {
        if (ind_x + 5 > x + len)
            SDL_RenderDrawLine(ren, ind_x, y + hei, x + len, y + hei);
        else
            SDL_RenderDrawLine(ren, ind_x, y + hei, ind_x + 5, y + hei);
    }
    for (int ind_y = y + step; ind_y <= y + hei; ind_y += 10) {
        if (ind_y + 5 > y + hei)
            SDL_RenderDrawLine(ren, x + len, ind_y, x + len, y + hei);
        else
            SDL_RenderDrawLine(ren, x + len, ind_y, x + len, ind_y + 5);
    }
}

void ShowLineSprite(int start_x, int start_y, int end_x, int end_y, std::string str) {
    SDL_Surface* surface = IMG_Load(str.c_str());
    if (!surface) {
        std::cout << "Failed to create surface\n";
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
    if (!texture) {
        std::cout << "Failed to create texture\n";
    }
    SDL_FreeSurface(surface);
    while (start_x + 55 < end_x) {
        SDL_Rect rect = { start_x, start_y, 55, 26 };
        if (texture) {
            SDL_RenderCopy(ren, texture, nullptr, &rect);
        }
        start_x += 55;
    }
    SDL_Rect rect = { end_x - 55, start_y, 55, 26 };
    if (texture) {
        SDL_RenderCopy(ren, texture, nullptr, &rect);
    }
    SDL_DestroyTexture(texture);
}

Uint32 ConvertColor(SDL_Color _color)
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 pixelColor = (_color.b << 24) + (_color.g << 16) + (_color.r << 8) + 255;
#else
    Uint32 pixelColor = (255 << 24) + (_color.r << 16) + (_color.g << 8) + _color.b;
#endif
    return pixelColor;
}

SDL_Texture* GetAreaTextrue(SDL_Rect rect, SDL_Renderer* renderer, SDL_Texture* source)
{
    SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
    SDL_SetRenderTarget(renderer, result);
    SDL_RenderCopy(renderer, source, &rect, NULL);
    // the folowing line should reset the target to default(the screen)
    SDL_SetRenderTarget(renderer, NULL);
    // I also removed the RenderPresent funcion as it is not needed here      
    return result;
}