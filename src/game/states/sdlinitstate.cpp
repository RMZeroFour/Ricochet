#include "game/states/sdlinitstate.h"

#include "game/states/crashstate.h"
#include "game/states/imguiinitstate.h"
#include "helpers/log_wrappers.h"

#include <SDL2/SDL_image.h>

Transition SDLInitState::Process()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR(_game.logger, "Failed to initialize SDL: {}", SDL_GetError());
		return Switch<CrashState>(_game);
	}

	SDL_Window* window{};
	SDL_Renderer* renderer{};
	if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) < 0)
	{
		LOG_ERROR(_game.logger, "Failed to create window and renderer: {}", SDL_GetError());
		return Switch<CrashState>(_game);
	}

	int w, h;
	if (SDL_GetRendererOutputSize(renderer, &w, &h) < 0)
	{
		LOG_ERROR(_game.logger, "Failed to get framebuffer dimensions: {}", SDL_GetError());
		return Switch<CrashState>(_game);
	}

	SDL_SetWindowTitle(window, "Ricochet");

	_game.sdl = SDLData{ window, renderer, w, h };

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
	{
		LOG_ERROR(_game.logger, "Failed to enable PNG loading: {}", IMG_GetError());
		return Switch<CrashState>(_game);
	}
	
	SDL_Texture* icon{ IMG_LoadTexture(renderer, "Icon.png") };
	_game.sdl->textures.Load("Icon", icon);
	LOG_INFO(_game.logger, "Loaded Icon texture");

	return Switch<ImGuiInitState>(_game);
}