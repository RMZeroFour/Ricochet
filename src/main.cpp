#include "statemachine/statemachine.h"
#include "generated/buildinfo.h"
#include "helpers/log_wrappers.h"
#include "game/states/argsparserstate.h"

#include <SDL2/SDL_main.h>
//#include <spdlog/sinks/stdout_color_sinks.h>

int main(int argc, char** argv)
{   
	GameData game{};

	// game.logger = spdlog::stdout_color_mt(Ricochet_NAME);
	// game.logger->set_pattern("%^[%T] %^[%L]%$ [%s:%#] %v");
	// game.logger->set_level(spdlog::level::debug);
	// game.logger->flush_on(spdlog::level::warn);
	// LOG_WARN(game.logger, "{}", "hello world!");
	// LOG_DEBUG(game.logger, "{}", "hello world!2");
	// LOG_ERROR(game.logger, "{}", "hello world!3");

	for (size_t i = 1; i < argc; i++)
		game.args.push_back(argv[i]);

	StateMachine fsm{ std::make_unique<ArgsParserState>(game) };
	
	while (!fsm.HasFinished())
		fsm.ProcessCurrent();
		
	return 0;
}