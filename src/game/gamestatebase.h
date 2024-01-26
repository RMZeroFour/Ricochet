#pragma once

#include "statemachine/statebase.h"
#include "game/gamedata.h"

class GameStateBase : public StateBase
{
protected:
	GameStateBase(GameData& game) : _game{ game } { }

protected:
	GameData& _game;
};