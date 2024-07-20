#include <Tails/Layers/Layer.hpp>
#include <Tails/States/State.hpp>
#include <Tails/Subsystems/LayerSubsystem.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    State* Layer::pushState(std::unique_ptr<State> state)
    {
        if (!state) return nullptr;

        m_states.push_back(std::move(state));
        getTopState()->outer = this;
        getTopState()->push();
        return getTopState();
    }

    State* Layer::getState(size_t index) const
    {
        if (isIndexValid(index))
            return m_states[index].get();

        return nullptr;
    }

    bool Layer::isIndexValid(size_t index) const
    {
        return index < m_states.size();
    }

    State* Layer::getActiveState() const
    {
        if (isIndexValid(m_activeState))
            return m_states[m_activeState].get();

        return nullptr;
    }

    void Layer::popState()
    {
        popState(m_activeState);
    }

    // all other popState methods point here
    void Layer::popState(State* state)
    {
        if (auto it = std::find_if(m_states.begin(), m_states.end(),
            [&](auto& uniqueState)
            {
                return uniqueState.get() == state;
            }); it == m_states.end())
            return;

        state->pop();
        state->pendingDestroy = true;
    }

    void Layer::popState(size_t index)
    {
        if (isIndexValid(index))
            popState(getState(index));
    }

    void Layer::preTick()
    {
        Tickable::preTick();

        for (auto& state : m_states)
        {
            state->preTick();

            if (state->pendingCreate)
            {
                state->pendingCreate = false;
                state->postPush();
            }
        }
    }

    void Layer::tick(float deltaTime)
    {
        if (m_states.empty()) return;

        for (size_t i {0}; i < m_states.size(); i++)
        {
            if (!m_states[i]->pendingCreate && (i == m_activeState || m_states[i]->tickWhileInactive))
                m_states[i]->tick(deltaTime);
        }
    }

    void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (size_t i {0}; i < m_states.size(); i++)
        {
            if (!m_states[i]->pendingCreate && (i == m_activeState || m_states[i]->drawWhileInactive))
                target.draw(*m_states[i], states);
        }
    }

    void Layer::postTick()
    {
        Tickable::postTick();

        for (size_t i {0}; i < m_states.size();)
        {
            m_states[i]->postTick();

            if (m_states[i]->pendingDestroy)
                m_states.erase(m_states.begin() + static_cast<long long>(i));
            else
                i++;
        }
    }

    void Layer::remove()
    {
        for (auto& state : m_states)
        {
            state->pop();
        }
    }

    void Layer::setZOrder(int zOrder)
    {
        m_zOrder = zOrder;
        getLayerSubsystem().sortLayers();
    }

    LayerSubsystem& Layer::getLayerSubsystem() const
    {
        return *dynamic_cast<LayerSubsystem*>(outer);
    }
}
