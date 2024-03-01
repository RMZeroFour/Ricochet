#include "states/dummystate.h"

#include "states/imguiquitstate.h"
#include "helpers/rect_extensions.h"

#if Ricochet_ENABLE_IMGUI
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Transition DummyState::Process()
{
	SDLData& sdl{ _game.sdl.value() };

	Texture ball{ sdl.textures.Fetch("Ball") };
	Texture paddle{ sdl.textures.Fetch("Paddle") };

	float leftAngle{ 0 };
	float rightAngle{ 0 };
	SDL_Point pivotOffset{ 23, 32 };

	bool running{ true };
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
#if Ricochet_ENABLE_IMGUI
			ImGui_ImplSDL2_ProcessEvent(&e);
#endif

			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		SDL_SetRenderDrawColor(sdl.renderer, 100, 149, 237, 255);
		SDL_RenderClear(sdl.renderer);

		SDL_Rect ballRect{ 0, 0, 48, 48 };
		SetCenter(ballRect, mouseX, mouseY);
		SDL_SetRenderDrawColor(sdl.renderer, 255, 0, 0, 255);
		SDL_RenderCopy(sdl.renderer, ball.texture, &ball.rect, &ballRect);

		SDL_Rect leftPaddleRect{ 0, 0, 128, 64 };
		AlignBottomLeftTo(leftPaddleRect, sdl.size);
		Translate(leftPaddleRect, 150, -100);
		SDL_Point leftPivot{ pivotOffset };
		SDL_RenderCopyEx(sdl.renderer, paddle.texture, &paddle.rect,
			&leftPaddleRect, leftAngle, &leftPivot, SDL_FLIP_NONE);

		SDL_Rect rightPaddleRect{ 0, 0, 128, 64 };
		AlignBottomRightTo(rightPaddleRect, sdl.size);
		Translate(rightPaddleRect, -150, -100);
		SDL_Point rightPivot{ 128 - pivotOffset.x, 64 - pivotOffset.y };
		SDL_RenderCopyEx(sdl.renderer, paddle.texture, &paddle.rect,
			&rightPaddleRect, rightAngle, &rightPivot, SDL_FLIP_HORIZONTAL);

		leftAngle += 0.02f;
		rightAngle += 0.04f;

#if Ricochet_ENABLE_IMGUI
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		ImGui::InputInt("Offset X", &pivotOffset.x);
		ImGui::InputInt("Offset Y", &pivotOffset.y);
		ImGui::DragFloat("Angle Right", &rightAngle, 1.0f, -360, 360);
		ImGui::DragFloat("Angle Left", &leftAngle, 1.0f, -360, 360);

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
#endif

		SDL_RenderPresent(sdl.renderer);
	}

	return Switch<ImGuiQuitState>(_game);
}
