#include "states/argsparserstate.h"
#include "statemachine.h"

#include <SDL2/SDL_main.h>

int main(int argc, char** argv)
{   
	GameData game{};
	StateMachine fsm{ std::make_unique<ArgsParserState>(argc, argv, game) };
	
	while (!fsm.HasFinished())
		fsm.ProcessCurrent();
		
	return 0;
}