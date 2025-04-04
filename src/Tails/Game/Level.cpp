#include <Tails/Game/Level.hpp>
#include <Tails/Game/Actor.hpp>
#include <Tails/Renderer/Renderer.hpp>

#include <algorithm>

namespace tails
{
    void CLevel::destroyActor(const CActor* actor)
    {
        if (const auto it = getActorIterator(actor); it != m_actors.end())
        {
            it->get()->flags.setBit(CActor::PendingKill);
        }
    }

    void CLevel::onTick(const float deltaSeconds)
    {
        // C-style because the actors can get reallocated when resizing the vector mid-iteration
        for (usize i {0}; i < m_actors.size(); i++)
        {
            m_actors[i]->onTick(deltaSeconds);

            for (usize j {0}; j < m_actors.size(); j++)
            {
                if (m_actors[i] == m_actors[j])
                    continue;
                
                if (m_actors[i]->isOverlapping(m_actors[j].get()))
                    m_actors[i]->onOverlap(m_actors[j].get());
            }
        }
    }

    void CLevel::onRender(IRenderer& renderer) const
    {
        for (const auto& actor : m_actors)
        {
            renderer.render(*actor);
        }
    }

    CActor* CLevel::spawnActor(std::unique_ptr<CActor> actor, const STransform2D& transform)
    {
        m_actors.emplace_back(std::move(actor));
        auto& result = *m_actors.back();
        result.m_owningLevel = this;
        result.onInitComponents();
        result.setTransform(transform);
        result.onSpawn();
        return &result;
    }

    void CLevel::cleanupActors()
    {
        for (auto it {m_actors.rbegin()}; it != m_actors.rend();)
        {
            if (it->get()->flags.isBitSet(CActor::PendingKill))
                it = decltype(it)(m_actors.erase(std::next(it).base()));
            else
                ++it;
        }
    }

    CLevel::ActorIterator CLevel::getActorIterator(const CActor* actor)
    {
        return std::find_if(m_actors.begin(), m_actors.end(),
            [actor](const std::unique_ptr<CActor>& uniqueActor)
            {
                return actor == uniqueActor.get();
            });
    }

    CLevel::ConstActorIterator CLevel::getActorIterator(const CActor* actor) const
    {
        return std::find_if(m_actors.begin(), m_actors.end(),
            [actor](const std::unique_ptr<CActor>& uniqueActor)
            {
                return actor == uniqueActor.get();
            });
    }

    bool CLevel::containsActor(const CActor* actor) const
    {
        return getActorIterator(actor) != m_actors.end();
    }
}
