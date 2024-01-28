#include "game/states/loginitstate.h"

#include "game/states/sdlinitstate.h"
#include "generated/buildinfo.h"
#include "helpers/log_wrappers.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <string>

Transition LogInitState::Process()
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

 	return Switch<SDLInitState>(_game);
}