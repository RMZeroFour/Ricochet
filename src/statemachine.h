#pragma once

#include "statebase.h"

#include <memory>
#include <stack>

class StateMachine
{
public:
    StateMachine(std::unique_ptr<StateBase> first)
        : _states{}
        , _finished{ false }
    { 
        _states.push(std::move(first));
    }

public:
    bool HasFinished() const { return _finished; }

    void ProcessCurrent();

private:
    bool _finished;
    std::stack<std::unique_ptr<StateBase>> _states;
};