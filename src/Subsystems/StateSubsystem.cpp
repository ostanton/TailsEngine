#include <Tails/Subsystems/StateSubsystem.hpp>
#include <Tails/States/State.hpp>
#include <Tails/Engine.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    StateSubsystem::StateSubsystem() = default;
    StateSubsystem::~StateSubsystem() = default;

    void StateSubsystem::pushState(std::unique_ptr<State> state)
    {
        // early return if the state we are pushing is invalid
        if (!state) return;

        state->pendingCreate = true;
        m_states.push_back(std::move(state));
        setupState(getActiveState());
    }

    void StateSubsystem::popState()
    {
        if (m_states.empty()) return;

        getActiveState()->removed();
        m_popState = true;
    }

    State* StateSubsystem::getActiveState() const
    {
        if (m_states.empty() || !m_states.back()) return nullptr;

        return m_states.back().get();
    }

    bool StateSubsystem::isStateActive(State* state) const
    {
        return state == getActiveState();
    }

    void StateSubsystem::init(Engine& engine)
    {

    }

    void StateSubsystem::preTick()
    {
        if (m_states.empty()) return;

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
        if (getActiveState())
            getActiveState()->tick(deltaTime);
    }

    void StateSubsystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // add options for non-active states to draw
        if (getActiveState())
            target.draw(*getActiveState(), states);
    }

    void StateSubsystem::postTick()
    {
        if (m_states.empty()) return;

        for (auto& state : m_states)
        {
            state->postTick();
        }

        if (m_popState)
        {
            m_states.pop_back();
        }
    }

    void StateSubsystem::setupState(State* state)
    {
        Debug::print("Setting up state...");
        if (!state)
        {
            Debug::print("State is invalid.");
            return;
        }
        state->outer = this;
        state->init(*this);
        if (state->m_customCameraSize.x == 0.f && state->m_customCameraSize.y == 0.f)
        {
            state->m_customCameraSize = getEngine().getRenderSettings().size;
        }
    }
}
