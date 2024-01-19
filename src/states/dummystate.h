#pragma once

#include "gamestatebase.h"

class DummyState : public GameStateBase
{
public:
    DummyState(GameData& game) : GameStateBase(game) { }

public:
    virtual void OnEnter() { }
    virtual Transition Process();
    virtual void OnExit() { }
};