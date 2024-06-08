#include <Tails/Subsystems/StateSubsystem.hpp>
#include <Tails/States/State.hpp>
#include <Tails/Engine.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    StateSubsystem::StateSubsystem()
    {

    }

    StateSubsystem::~StateSubsystem()
    {

    }

    void StateSubsystem::pushState(std::unique_ptr<State> state)
    {
        m_states.push_back(std::move(state));
        setupState(getActiveState(), false);
    }

    void StateSubsystem::popState()
    {
        if (m_states.empty()) return;

        getActiveState()->removed();
        m_popState = true;
    }

    State* StateSubsystem::getActiveState() const
    {
        return m_activeState;
    }

    bool StateSubsystem::isStateActive(State* state) const
    {
        return state == getActiveState();
    }

    void StateSubsystem::init()
    {

    }

    void StateSubsystem::preTick()
    {
        for (auto& state : m_states)
        {
            state->preTick();

            if (state->pendingCreate)
            {
                state->pendingCreate = false;
                state->added();
                m_activeState = state.get();
            }
        }
    }

    void StateSubsystem::tick(float deltaTime)
    {
        // add options for non-active states to tick
        m_activeState->tick(deltaTime);
    }

    void StateSubsystem::draw(sf::RenderTarget& target)
    {
        // add options for non-active states to draw
        target.draw(*m_activeState);
    }

    void StateSubsystem::postTick()
    {
        for (auto& state : m_states)
        {
            state->postTick();
        }

        if (m_popState)
        {
            m_states.pop_back();
            m_activeState = m_states.back().get();
        }
    }

    void StateSubsystem::setupState(State* state, bool callCreate)
    {
        state->outer = this;
        if (callCreate) state->create();
        // TODO - state camera things
        //state->setCameraResolution();
        //state->setCameraPosition();
        state->added();
    }
}
