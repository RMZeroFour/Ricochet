#pragma once

#include "game/gamestatebase.h"

class CrashState : public GameStateBase
{
public:
	CrashState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { }
	virtual Transition Process();
	virtual void OnExit() { }
};