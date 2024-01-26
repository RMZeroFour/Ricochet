#pragma once

#include "game/gamestatebase.h"

class ArgsParserState : public GameStateBase
{
public:
	ArgsParserState(GameData& game) : GameStateBase(game) { }

public:
	virtual void OnEnter() { }
	virtual Transition Process();
	virtual void OnExit() { }
};