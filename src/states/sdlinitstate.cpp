#include "states/sdlinitstate.h"

#include "states/dummystate.h"
#include "states/sdlquitstate.h"

// static void AdjustLoggingPriority()
// {
//     SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
// }

Transition SDLInitState::Process()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL: %s", SDL_GetError());
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return Switch<SDLQuitState>(_game);
    }

    SDL_Window* window{};
    SDL_Renderer* renderer{};
    if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) < 0)
    {
        //SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create window and renderer: %s", SDL_GetError());
        SDL_Log("Failed to create window and renderer: %s", SDL_GetError());
        return Switch<SDLQuitState>(_game);
    }
        
    SDL_SetWindowTitle(window, "Ricochet");
    
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    _game.sdl = { window, renderer, w, h };

    return Switch<DummyState>(_game);
}