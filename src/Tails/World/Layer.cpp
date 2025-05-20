#include <Tails/World/Layer.hpp>
#include <Tails/World/Actor.hpp>

#include <algorithm>

namespace tails
{
    void CLayer::onTick(const float deltaSeconds)
    {
        for (usize i {0}; i < m_actors.size(); i++)
        {
            m_actors[i]->onTick(deltaSeconds);
        }
    }

    void CLayer::onRender() const
    {
        for (usize i {0}; i < m_actors.size(); i++)
        {
            m_actors[i]->onRender();
        }
    }

    void CLayer::addActor(CActor* actor)
    {
        m_actors.push_back(actor);
    }

    void CLayer::removeActor(const CActor* actor)
    {
        if (const auto it = std::find(m_actors.begin(), m_actors.end(), actor);
            it != m_actors.end())
        {
            m_actors.erase(it);
        }
    }
}
