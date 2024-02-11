#include "game/states/loginitstate.h"

#include "game/states/sdlinitstate.h"
#include "buildinfo.h"
#include "helpers/log_wrappers.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <string>

namespace
{
	void CreateLogger(GameData& _game)
	{
		std::string logFilepath;
		if (_game.args({ "-l", "--log" }) >> logFilepath)
		{
			_game.logger = spdlog::basic_logger_mt(Ricochet_NAME, logFilepath);
			_game.logger->set_pattern("[%T] [%L] [%s:%#] %v");
		}
		else
		{
			_game.logger = spdlog::stdout_color_mt(Ricochet_NAME);
			_game.logger->set_pattern("[%T] %^[%L]%$ [%s:%#] %v");
		}
		
		_game.logger->set_level(spdlog::level::debug);
		_game.logger->flush_on(spdlog::level::warn);
	}

	void LogBuildInfo(GameData& _game)
	{
		LOG_INFO(_game.logger, "{} v{}", Ricochet_NAME, Ricochet_VERSION);
		LOG_INFO(_game.logger, "{}: {}", "Ricochet_DEVELOPER_MODE", 
			Ricochet_DEVELOPER_MODE ? "ON" : "OFF");
		LOG_INFO(_game.logger, "{}: {}", "Ricochet_ENABLE_DEBUG_LOGGING", 
			Ricochet_ENABLE_DEBUG_LOGGING ? "ON" : "OFF");
		LOG_INFO(_game.logger, "{}: {}", "Ricochet_ENABLE_IMGUI", 
			Ricochet_ENABLE_IMGUI ? "ON" : "OFF");
	}
}

Transition LogInitState::Process()
{
	CreateLogger(_game);
	LogBuildInfo(_game);
	
 	return Switch<SDLInitState>(_game);
}