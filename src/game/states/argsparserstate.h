#pragma once

#include "game/gamestatebase.h"

class ArgsParserState : public GameStateBase
{
public:
	ArgsParserState(int argc, char** argv, GameData& game) 
		: GameStateBase(game) 
	{
		_argc = argc;
		_argv = argv;
	}

public:
	virtual void OnEnter() { }
	virtual Transition Process();
	virtual void OnExit() { }
	
private:
	int _argc;
	char** _argv;
};