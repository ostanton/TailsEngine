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
        state->pendingCreate = true;
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
        return m_states.back().get();
    }

    bool StateSubsystem::isStateActive(State* state) const
    {
        return state == getActiveState();
    }

    void StateSubsystem::init(Engine& engine)
    {
        emplaceState<State>();
        Debug::print("Finished init of StateSubsystem.");
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
            }
        }
    }

    void StateSubsystem::tick(float deltaTime)
    {
        // add options for non-active states to tick
        getActiveState()->tick(deltaTime);
    }

    void StateSubsystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // add options for non-active states to draw
        target.draw(*getActiveState(), states);
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
        }
    }

    void StateSubsystem::setupState(State* state, bool callCreate)
    {
        Debug::print("Setting up state...");
        if (!state)
        {
            Debug::print("State is invalid.");
            return;
        }
        state->outer = this;
        state->init(*this);
        if (callCreate) state->create();
        // TODO - state camera things
        //state->setCameraResolution();
        //state->setCameraPosition();
    }
}
