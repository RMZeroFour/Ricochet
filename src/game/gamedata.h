#pragma once

#include <SDL2/SDL.h>

#include <optional>
#include <string>
#include <vector>

struct SDLData
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	int width;
	int height;
};

struct GameData
{
	std::vector<std::string> args;
	std::optional<SDLData> sdl;
};
