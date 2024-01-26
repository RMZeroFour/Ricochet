#pragma once

#include "game/gamestatebase.h"

class SDLQuitState : public GameStateBase
{
public:
	SDLQuitState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { }
	virtual Transition Process();
	virtual void OnExit() { }
};