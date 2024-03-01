#pragma once

#include "gamestatebase.h"
#include "helpers/log_wrappers.h"

class CrashState : public GameStateBase
{
public:
	CrashState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { LOG_DEBUG(_game.logger, "Entered CrashState"); }
	virtual Transition Process();
	virtual void OnExit() { LOG_DEBUG(_game.logger, "Exited CrashState"); }
};