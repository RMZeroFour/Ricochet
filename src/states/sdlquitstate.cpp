#include "states/sdlquitstate.h"

#include <SDL2/SDL_image.h>

Transition SDLQuitState::Process()
{
	_game.sdl->textures.UnregisterAll();
	LOG_INFO(_game.logger, "Unloaded all textures");

	IMG_Quit();

	SDL_DestroyRenderer(_game.sdl->renderer);
	SDL_DestroyWindow(_game.sdl->window);
	_game.sdl.reset();
	
	SDL_Quit();

	return Quit();
}