#include "states/imguiinitstate.h"

#include "states/dummystate.h"

#if Ricochet_ENABLE_IMGUI
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#endif

Transition ImGuiInitState::Process()
{
	SDLData& sdl{ _game.sdl.value() };

#if Ricochet_ENABLE_IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(sdl.window, sdl.renderer);
	ImGui_ImplSDLRenderer2_Init(sdl.renderer);
#endif

	return Switch<DummyState>(_game);
}