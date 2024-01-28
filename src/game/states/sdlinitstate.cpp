#include "game/states/sdlinitstate.h"

#include "game/states/crashstate.h"
#include "game/states/imguiinitstate.h"
#include "helpers/log_wrappers.h"

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

	_game.sdl = { window, renderer, w, h };

	return Switch<ImGuiInitState>(_game);
}