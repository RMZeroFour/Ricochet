#include <SDL2/SDL.h>

int main(int, char**)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    SDL_Window* window{};
    SDL_Renderer* renderer{};
    if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) < 0)
    {
        SDL_Log("Failed to create window and renderer: %s", SDL_GetError());
        return -1;
    }
    
    SDL_SetWindowTitle(window, "Ricochet");

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

        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}