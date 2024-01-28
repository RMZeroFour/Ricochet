#pragma once

#include "game/gamestatebase.h"

class ImGuiInitState : public GameStateBase
{
public:
	ImGuiInitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { }
	virtual Transition Process();
	virtual void OnExit() { }
};