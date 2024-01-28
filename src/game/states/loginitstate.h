#pragma once

#include "game/gamestatebase.h"

class LogInitState : public GameStateBase
{
public:
	LogInitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { }
	virtual Transition Process();
	virtual void OnExit() { }
};