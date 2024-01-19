#include "states/sdlquitstate.h"

Transition SDLQuitState::Process()
{
    if (_game.sdl.has_value())
    {
        SDL_DestroyRenderer(_game.sdl->renderer);
        SDL_DestroyWindow(_game.sdl->window);
        _game.sdl.reset();
    }

    SDL_Quit();

    return Quit();
}