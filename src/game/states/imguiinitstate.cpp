#include "game/states/imguiinitstate.h"

#include "game/states/dummystate.h"
#include "helpers/imgui_block.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Transition ImGuiInitState::Process()
{
	SDLData& sdl{ _game.sdl.value() };
	
	IMGUI_BLOCK_BEGIN();
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		
		ImGui::StyleColorsDark();
		
		ImGui_ImplSDL2_InitForSDLRenderer(sdl.window, sdl.renderer);
		ImGui_ImplSDLRenderer2_Init(sdl.renderer);
	}
	IMGUI_BLOCK_END();

	return Switch<DummyState>(_game);
}