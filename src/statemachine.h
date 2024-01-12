#pragma once

#include "statebase.h"
#include "transition.h"

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

    void ProcessCurrent()
    {
        _states.top()->OnEnter();
        Transition t{ _states.top()->Process() };
        _states.top()->OnExit();

        if (std::holds_alternative<PopTransition>(t))
        {
            _states.pop();
        }
        else if (std::holds_alternative<PushTransition>(t))
        {
            _states.push(std::move(std::get<PushTransition>(t).state));
        }
        else if (std::holds_alternative<SwitchTransition>(t))
        {
            _states.pop();
            _states.push(std::move(std::get<SwitchTransition>(t).state));
        }
        else if (std::holds_alternative<QuitTransition>(t))
        {
            _finished = true;
        }
    }

private:
    bool _finished;
    std::stack<std::unique_ptr<StateBase>> _states;
};