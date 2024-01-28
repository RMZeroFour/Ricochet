#pragma once

#include "game/gamestatebase.h"
#include "helpers/log_wrappers.h"

class LogInitState : public GameStateBase
{
public:
	LogInitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { }
	virtual Transition Process();
	virtual void OnExit() { LOG_DEBUG(_game.logger, "Exited LogInitState"); }
};