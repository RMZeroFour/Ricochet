#pragma once

#include "game/sdldata.h"

#include <spdlog/spdlog.h>
#include <argh.h>

#include <memory>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

struct GameData
{
	argh::parser args;
	std::shared_ptr<spdlog::logger> logger;
	std::optional<SDLData> sdl;
	
	std::filesystem::path readRoot;
	std::filesystem::path writeRoot;
};
