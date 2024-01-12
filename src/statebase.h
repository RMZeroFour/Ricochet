#pragma once

#include "transition.h"

class StateBase
{
public:
    virtual ~StateBase() = default;

public:
    virtual void OnEnter() = 0;
    virtual Transition Process() = 0;
    virtual void OnExit() = 0;
};