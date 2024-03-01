#pragma once

#include "statebase.h"
#include "gamedata.h"

class GameStateBase : public StateBase
{
protected:
	GameStateBase(GameData& game) : _game{ game } { }

protected:
	GameData& _game;
};