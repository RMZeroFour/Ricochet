#pragma once

#include "gamestatebase.h"

class SDLInitState : public GameStateBase
{
public:
    SDLInitState(GameData& game) : GameStateBase(game) { }

public:
    virtual void OnEnter() { }
    virtual Transition Process();
    virtual void OnExit() { }
};