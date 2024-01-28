#include "game/states/sdlquitstate.h"

Transition SDLQuitState::Process()
{
	SDL_DestroyRenderer(_game.sdl->renderer);
	SDL_DestroyWindow(_game.sdl->window);
	_game.sdl.reset();
	
	SDL_Quit();

	return Quit();
}