#include "states/sdlinitstate.h"

#include "states/crashstate.h"
#include "states/imguiinitstate.h"
#include "helpers/log_wrappers.h"

#include <SDL2/SDL_image.h>
#include "sdlinitstate.h"

namespace
{
	void SetStaticRoot(GameData& _game)
	{
		char* basePath{ SDL_GetBasePath() };
		std::filesystem::path staticRoot{ basePath };
		SDL_free(basePath);

#if Ricochet_PLATFORM_LINUX
		staticRoot /= "../share/ricochet";
#else 
		staticRoot /= "assets";
#endif

		_game.staticRoot = staticRoot.lexically_normal();
	}

	void SetDynamicRoot(GameData& _game)
	{
		char* prefPath{ SDL_GetPrefPath(Ricochet_MAINTAINER, Ricochet_NAME) };
		_game.dynamicRoot = std::filesystem::path{ prefPath };
		SDL_free(prefPath);
	}

	bool TryLoadTexture(GameData& _game, const std::string& key, const std::filesystem::path& path)
	{
		SDL_Texture* tex{ IMG_LoadTexture(_game.sdl->renderer, path.string().c_str()) };

		if (tex != nullptr)
		{
			_game.sdl->textures.Register(key, tex);

			LOG_INFO(_game.logger, "Loaded texture '{}' ({})",
				key.c_str(), path.string().c_str());
			return true;
		}
		else
		{
			LOG_ERROR(_game.logger, "Could not load texture '{}' ({})",
				key.c_str(), path.string().c_str());
			return false;
		}
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

	int w{}, h{};
	if (SDL_GetRendererOutputSize(renderer, &w, &h) < 0)
	{
		LOG_ERROR(_game.logger, "Failed to get framebuffer dimensions: {}", SDL_GetError());
		return Switch<CrashState>(_game);
	}

	SDL_SetWindowTitle(window, "Ricochet");

	_game.sdl = SDLData{ window, renderer, w, h };
	SetStaticRoot(_game);
	SetDynamicRoot(_game);

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
	{
		LOG_ERROR(_game.logger, "Failed to enable PNG loading: {}", IMG_GetError());
		return Switch<CrashState>(_game);
	}

	// Should be a separate state
	const std::unordered_map<std::string, std::string> textures{
		{"Ball", "ball.png"},
		{"Paddle", "paddle.png"}
	};
	for (auto& [k, v] : textures)
	{
		if (!TryLoadTexture(_game, k, _game.staticRoot / "textures" / v))
		{
			return Switch<CrashState>(_game);
		}
	}

	return Switch<ImGuiInitState>(_game);
}