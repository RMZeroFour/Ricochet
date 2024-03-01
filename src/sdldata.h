#pragma once

#include "texturecache.h"

#include <SDL2/SDL.h>

class SDLData
{
public:
	SDLData(SDL_Window* win, SDL_Renderer* ren, int w, int h)
		: window{ win }
		, renderer{ ren }
		, size{ 0, 0, w, h }
		, textures{}
	{ }

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect size;
	TextureCache textures;
};