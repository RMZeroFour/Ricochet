#pragma once

#include "game/texturecache.h"

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>
#include <argh.h>

#include <memory>
#include <optional>
#include <string>
#include <vector>

struct SDLData
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	int width;
	int height;
	
	TextureCache textures;
};

struct GameData
{
	argh::parser args;
	std::shared_ptr<spdlog::logger> logger;
	std::optional<SDLData> sdl;
};
