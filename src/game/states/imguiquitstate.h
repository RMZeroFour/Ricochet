#pragma once

#include "game/gamestatebase.h"

class ImGuiQuitState : public GameStateBase
{
public:
	ImGuiQuitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { }
	virtual Transition Process();
	virtual void OnExit() { }
};