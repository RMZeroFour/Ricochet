#include "gamedata.h"
#include "statemachine.h"
#include "states/sdlinitstate.h"

#include <SDL2/SDL_main.h>

int main(int argc, char** argv)
{
    GameData game{};
    StateMachine fsm{ std::make_unique<SDLInitState>(game) };
    
    while (!fsm.HasFinished())
        fsm.ProcessCurrent();

    return 0;
}