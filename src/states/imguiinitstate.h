#pragma once

#include "gamestatebase.h"
#include "helpers/log_wrappers.h"

class ImGuiInitState : public GameStateBase
{
public:
	ImGuiInitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { LOG_DEBUG(_game.logger, "Entered ImGuiInitState"); }
	virtual Transition Process();
	virtual void OnExit() { LOG_DEBUG(_game.logger, "Exited ImGuiInitState"); }
};