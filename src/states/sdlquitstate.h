#pragma once

#include "gamestatebase.h"
#include "helpers/log_wrappers.h"

class SDLQuitState : public GameStateBase
{
public:
	SDLQuitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { LOG_DEBUG(_game.logger, "Entered SDLQuitState"); }
	virtual Transition Process();
	virtual void OnExit() { LOG_DEBUG(_game.logger, "Exited SDLQuitState"); }
};