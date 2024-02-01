#include "game/states/dummystate.h"

#include "game/states/imguiquitstate.h"
#include "helpers/imgui_block.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Transition DummyState::Process()
{
	SDLData& sdl{ _game.sdl.value() };

	Texture i{ sdl.textures.Fetch("Icon") };
	
	bool running{ true };
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			IMGUI_BLOCK_BEGIN();
			{
				ImGui_ImplSDL2_ProcessEvent(&e);
			}
			IMGUI_BLOCK_END();

			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}

		SDL_SetRenderDrawColor(sdl.renderer, 100, 149, 237, 255);
		SDL_RenderClear(sdl.renderer);

		int x, y;
		SDL_GetMouseState(&x, &y);
		SDL_Rect r{ x - 32, y - 32, 64, 64 };
		SDL_SetRenderDrawColor(sdl.renderer, 255, 0, 0, 255);
		SDL_RenderCopy(sdl.renderer, i.texture, &i.rect, &r);
		r.x = sdl.width - r.x;
		SDL_RenderCopy(sdl.renderer, i.texture, &i.rect, &r);
		r.y = sdl.height - r.y;
		SDL_RenderCopy(sdl.renderer, i.texture, &i.rect, &r);
		r.x = sdl.width - r.x;
		SDL_RenderCopy(sdl.renderer, i.texture, &i.rect, &r);

		IMGUI_BLOCK_BEGIN();
		{
			ImGui_ImplSDLRenderer2_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();
			
			ImGui::Render();
			ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		}
		IMGUI_BLOCK_END();

		SDL_RenderPresent(sdl.renderer);
	}
	
	return Switch<ImGuiQuitState>(_game);
}