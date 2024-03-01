#include "states/imguiquitstate.h"

#include "states/sdlquitstate.h"

#if Ricochet_ENABLE_IMGUI
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#endif

Transition ImGuiQuitState::Process()
{
#if Ricochet_ENABLE_IMGUI
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
#endif

	return Switch<SDLQuitState>(_game);
}