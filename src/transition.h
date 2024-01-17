#pragma once

#include <memory>
#include <variant>

class StateBase;

struct PopTransition { };
struct QuitTransition { };
struct PushTransition { std::unique_ptr<StateBase> state; };
struct SwitchTransition { std::unique_ptr<StateBase> state; };

using Transition = std::variant<PopTransition, QuitTransition,
    PushTransition, SwitchTransition>;

inline Transition Pop() 
{
    static PopTransition p{};
    return p; 
}

inline Transition Quit()
{
    static QuitTransition q{};
    return q;
}

template<typename TState, class... Args>
Transition Push(Args&&... args) 
{
    return PushTransition{ std::make_unique<TState>(args...) };
}

template<typename TState, class... Args>
Transition Switch(Args&&... args) 
{
    return SwitchTransition{ std::make_unique<TState>(args...) };
}
