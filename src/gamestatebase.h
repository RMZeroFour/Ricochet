#pragma once

#include "gamedata.h"
#include "statebase.h"

class GameStateBase : public StateBase
{
protected:
    GameStateBase(GameData& game) : _game{ game } { }

protected:
    GameData& _game;
};