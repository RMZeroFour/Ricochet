#pragma once

#include <SDL2/SDL.h>

#include <optional>

struct SDLData
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    int width;
    int height;
};

struct GameData
{
    std::optional<SDLData> sdl;
};