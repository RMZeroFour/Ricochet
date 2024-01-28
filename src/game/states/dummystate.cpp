#include "game/states/dummystate.h"

#include "game/states/imguiquitstate.h"
#include "helpers/imgui_block.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Transition DummyState::Process()
{
	if (!_game.sdl.has_value())
		return Switch<ImGuiQuitState>(_game);
	SDLData& sdl{ _game.sdl.value() };

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
		SDL_Rect r{ x - 10, y - 10, 20, 20 };
		SDL_SetRenderDrawColor(sdl.renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(sdl.renderer, &r);
		r.x = sdl.width - r.x;
		SDL_RenderFillRect(sdl.renderer, &r);
		r.y = sdl.height - r.y;
		SDL_RenderFillRect(sdl.renderer, &r);
		r.x = sdl.width - r.x;
		SDL_RenderFillRect(sdl.renderer, &r);

		IMGUI_BLOCK_BEGIN();
		{
			ImGui_ImplSDLRenderer2_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();

			ImGui::Render();
			ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
		}
		IMGUI_BLOCK_END();

		SDL_RenderPresent(sdl.renderer);
	}

	return Switch<ImGuiQuitState>(_game);
}