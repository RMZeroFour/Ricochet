#include "game/states/dummystate.h"

#include "game/states/sdlquitstate.h"

Transition DummyState::Process()
{
	if (!_game.sdl.has_value())
		return Switch<SDLQuitState>(_game);

	SDLData& sdl{ _game.sdl.value() };

	bool running{ true };
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}

		SDL_SetRenderDrawColor(sdl.renderer, 100, 149, 237, 255);
		SDL_RenderClear(sdl.renderer);

		int x, y;
		SDL_GetMouseState(&x, &y);
		SDL_Rect r{ x - 10, y - 10, 20, 20 };
		SDL_SetRenderDrawColor(sdl.renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(sdl.renderer, &r);
		r.x = sdl.width - r.x;
		SDL_RenderFillRect(sdl.renderer, &r);
		r.y = sdl.height - r.y;
		SDL_RenderFillRect(sdl.renderer, &r);
		r.x = sdl.width - r.x;
		SDL_RenderFillRect(sdl.renderer, &r);

		SDL_RenderPresent(sdl.renderer);
	}

	return Push<SDLQuitState>(_game);
}