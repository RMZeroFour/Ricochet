#include "statemachine/statemachine.h"
#include "generated/buildinfo.h"
#include "helpers/log_wrappers.h"
#include "game/states/argsparserstate.h"

#include <SDL2/SDL_main.h>

int main(int argc, char** argv)
{   
	GameData game{};
	for (size_t i = 1; i < argc; i++)
		game.args.push_back(argv[i]);

	StateMachine fsm{ std::make_unique<ArgsParserState>(game) };
	
	while (!fsm.HasFinished())
		fsm.ProcessCurrent();
		
	return 0;
}