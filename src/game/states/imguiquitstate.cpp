#include "game/states/imguiquitstate.h"

#include "game/states/sdlquitstate.h"
#include "helpers/imgui_block.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

Transition ImGuiQuitState::Process()
{
	IMGUI_BLOCK_BEGIN();
	
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	IMGUI_BLOCK_END();

	return Switch<SDLQuitState>(_game);
}