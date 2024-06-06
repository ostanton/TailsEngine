#include <Tails/StateStack.hpp>
#include <Tails/State.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Debug.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

namespace tails
{
    StateStack::StateStack()
    {

    }

    StateStack::~StateStack()
    {

    }

    void StateStack::pushState(std::unique_ptr<State> state)
    {
        initState(state.get());
        state->added();
        m_states.push_back(std::move(state));
    }

    void StateStack::popState()
    {
        if (!activeState()) return;

        std::cout << "Popping " << typeid(*activeState()).name() << "...\n";

        activeState()->removed();
        m_states.pop_back();
    }

    std::vector<std::unique_ptr<State>>& StateStack::getVector()
    {
        return m_states;
    }

    Engine& StateStack::getEngine()
    {
        return *getTypedOuter<Engine>();
    }

    State* StateStack::activeState() const
    {
        return m_states[m_states.size() - 1].get();
    }

    bool StateStack::isStateActive(State* state) const
    {
        return state == activeState();
    }

    void StateStack::preTick()
    {
        for (auto& state : m_states)
        {
            state->preTick();
        }
    }

    void StateStack::tick(float deltaTime)
    {
        if (m_states.empty()) return;

        for (auto& state : m_states)
        {
            if (state.get() == activeState())
            {
                state->tick(deltaTime);
                continue;
            }

            if (state->tickWhileInactive) state->tick(deltaTime);
        }
    }

    void StateStack::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (m_states.empty()) return;

        for (auto& state : m_states)
        {
            if (state.get() == activeState())
            {
                target.setView(state->getCamera());
                target.draw(*state, states);
                target.setView(target.getDefaultView());
                continue;
            }

            if (state->drawWhileInactive)
            {
                target.setView(state->getCamera());
                target.draw(*state, states);
                target.setView(target.getDefaultView());
            }
        }
    }

    void StateStack::postTick()
    {
        for (auto& state : m_states)
        {
            state->postTick();
        }
    }

    void StateStack:: initState(State* state)
    {
        std::cout << "  " << typeid(*state).name() << " state initialising\n";
        state->outer = this;
        state->setCameraResolution(m_defaultCameraRes);
        state->setCameraPosition(m_defaultCameraRes / 2.f);
    }

    void StateStack::addState(State* state)
    {
        initState(state);
        state->create();
        state->added();
    }

    void StateStack::removeStates()
    {
        Debug::print("Removing states...");

        for (auto& state : m_states)
        {
            state->removed();
            std::cout << "  " << typeid(*state).name() << " removed.\n";
        }

        Debug::print("States removed!\n");
    }
}
