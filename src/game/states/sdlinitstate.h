#pragma once

#include "game/gamestatebase.h"
#include "helpers/log_wrappers.h"

class SDLInitState : public GameStateBase
{
public:
	SDLInitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { LOG_DEBUG(_game.logger, "Entered SDLInitState"); }
	virtual Transition Process();
	virtual void OnExit() { LOG_DEBUG(_game.logger, "Exited SDLInitState"); }
};