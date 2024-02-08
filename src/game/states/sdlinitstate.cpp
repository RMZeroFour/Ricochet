#include "game/states/sdlinitstate.h"

#include "game/states/crashstate.h"
#include "game/states/imguiinitstate.h"
#include "helpers/log_wrappers.h"

#include <SDL2/SDL_image.h>
#include "sdlinitstate.h"

namespace
{
	void SetReadPath(GameData& _game)
	{
		char* basePath{ SDL_GetBasePath() };
		std::filesystem::path readRoot{ basePath };
		readRoot /= Ricochet_DATA_DIR;
		_game.readRoot = readRoot.lexically_normal();
		SDL_free(basePath);
	}
	
	void SetWritePath(GameData& _game)
	{
		char* prefPath{ SDL_GetPrefPath(Ricochet_MAINTAINER, Ricochet_NAME) };
		_game.writeRoot = std::filesystem::path{ prefPath };
		SDL_free(prefPath);
	}
}

Transition SDLInitState::Process()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR(_game.logger, "Failed to initialize SDL: {}", SDL_GetError());
		return Switch<CrashState>(_game);
	}

	SDL_Window* window{};
	SDL_Renderer* renderer{};
	if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) < 0)
	{
		LOG_ERROR(_game.logger, "Failed to create window and renderer: {}", SDL_GetError());
		return Switch<CrashState>(_game);
	}

	int w, h;
	if (SDL_GetRendererOutputSize(renderer, &w, &h) < 0)
	{
		LOG_ERROR(_game.logger, "Failed to get framebuffer dimensions: {}", SDL_GetError());
		return Switch<CrashState>(_game);
	}

	SDL_SetWindowTitle(window, "Ricochet");

	_game.sdl = SDLData{ window, renderer, w, h };
	SetReadPath(_game);
	SetWritePath(_game);

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
	{
		LOG_ERROR(_game.logger, "Failed to enable PNG loading: {}", IMG_GetError());
		return Switch<CrashState>(_game);
	}

	std::filesystem::path iconPath{ _game.readRoot / "app" / "Icon.png" };
	SDL_Texture* icon{ IMG_LoadTexture(renderer, iconPath.string().c_str()) };
	LOG_INFO(_game.logger, "Loaded 'Icon' texture ({})", iconPath.string().c_str());
	_game.sdl->textures.Register("Icon", icon);

	return Switch<ImGuiInitState>(_game);
}