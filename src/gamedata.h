#pragma once

#include "sdldata.h"

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
	
	std::filesystem::path staticRoot;
	std::filesystem::path dynamicRoot;
};
