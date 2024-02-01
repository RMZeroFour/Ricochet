#include "game/states/sdlquitstate.h"

#include <SDL2/SDL_image.h>

Transition SDLQuitState::Process()
{
	IMG_Quit();

	SDL_DestroyRenderer(_game.sdl->renderer);
	SDL_DestroyWindow(_game.sdl->window);
	_game.sdl.reset();
	
	SDL_Quit();

	return Quit();
}