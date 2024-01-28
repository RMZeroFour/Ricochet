#pragma once

#include "game/gamestatebase.h"
#include "helpers/log_wrappers.h"

class DummyState : public GameStateBase
{
public:
	DummyState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { LOG_DEBUG(_game.logger, "Entered DummyState"); }
	virtual Transition Process();
	virtual void OnExit() { LOG_DEBUG(_game.logger, "Exited DummyState"); }
};