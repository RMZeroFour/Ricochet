#pragma once

#include "game/gamestatebase.h"
#include "helpers/log_wrappers.h"

class ImGuiQuitState : public GameStateBase
{
public:
	ImGuiQuitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { LOG_DEBUG(_game.logger, "Entered ImGuiQuitState"); }
	virtual Transition Process();
	virtual void OnExit() { LOG_DEBUG(_game.logger, "Exited ImGuiQuitState"); }
};