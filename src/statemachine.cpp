#include "statemachine.h"

#include "transition.h"

void StateMachine::ProcessCurrent()
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