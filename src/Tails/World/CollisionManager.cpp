#include <Tails/World/CollisionManager.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Components/Component.hpp>

#include <unordered_set>

namespace tails
{
    void CCollisionManager::beginCollisions()
    {
        m_currentComponentCollisions.clear();
        m_currentActorCollisions.clear();
        m_actorCollisionsStarted.clear();
    }

    void CCollisionManager::endCollisions()
    {
        m_previousComponentCollisions = std::move(m_currentComponentCollisions);
        m_previousActorCollisions = std::move(m_currentActorCollisions);
    }

    void CCollisionManager::registerCollision(CComponent* compA, CComponent* compB)
    {
        const SComponentCollisionPair pair {compA, compB};
        m_currentComponentCollisions.insert(pair);

        auto const actorA = compA->getOwner();
        auto const actorB = compB->getOwner();
        if (actorA && actorB && actorA != actorB)
        {
            m_currentActorCollisions.insert({actorA, actorB});
        }
    }

    bool CCollisionManager::hasActorCollisionStarted(CActor* actorA, CActor* actorB) const noexcept
    {
        return m_actorCollisionsStarted.contains({actorA, actorB});
    }

    void CCollisionManager::markActorCollisionStarted(CActor* actorA, CActor* actorB) noexcept
    {
        m_actorCollisionsStarted.insert({actorA, actorB});
    }

    bool CCollisionManager::didCollisionStart(CComponent* compA, CComponent* compB) const noexcept
    {
        const SComponentCollisionPair pair {compA, compB};
        return m_currentComponentCollisions.contains(pair) &&
            !m_previousComponentCollisions.contains(pair);
    }

    bool CCollisionManager::didCollisionStart(CActor* actorA, CActor* actorB) const noexcept
    {
        const SActorCollisionPair pair {actorA, actorB};
        return m_currentActorCollisions.contains(pair) &&
            !m_previousActorCollisions.contains(pair);
    }

    bool CCollisionManager::areColliding(const CComponent* compA, const CComponent* compB) const noexcept
    {
        // const_cast is safe here as the original components are non-const, and we aren't modifying them anyway
        return m_currentComponentCollisions.contains({
            const_cast<CComponent*>(compA),
            const_cast<CComponent*>(compB)
        });
    }

    bool CCollisionManager::areColliding(const CActor* actorA, const CActor* actorB) const noexcept
    {
        return m_currentActorCollisions.contains({
            const_cast<CActor*>(actorA),
            const_cast<CActor*>(actorB)
        });
    }

    std::vector<CComponent*> CCollisionManager::getCollisionsFor(const CComponent* component) const noexcept
    {
        std::vector<CComponent*> result;
        for (auto [compA, compB] : m_currentComponentCollisions)
        {
            if (compA == component)
                result.emplace_back(compB);
            else if (compB == component)
                result.emplace_back(compA);
        }
        return result;
    }

    std::vector<CActor*> CCollisionManager::getCollisionsFor(const CActor* actor) const noexcept
    {
        std::vector<CActor*> result;

        // tracks duplicate actors if multiple of its components have active collisions
        std::unordered_set<CActor*> collided;

        for (auto [compA, compB] : m_currentComponentCollisions)
        {
            auto const ownerA = compA->getOwner();
            auto const ownerB = compB->getOwner();

            if (ownerA == actor && collided.insert(ownerB).second)
                result.emplace_back(ownerB);
            else if (ownerB == actor && collided.insert(ownerA).second)
                result.emplace_back(ownerA);
        }
        return result;
    }

    void CCollisionManager::cleanupCollisions(const CActor* actor) noexcept
    {
        // collect the actor's components in an unordered_set for faster lookup
        std::unordered_set<const CComponent*> actorComponents;
        actorComponents.reserve(actor->m_components.size());
        for (const auto& comp : actor->m_components)
            actorComponents.insert(comp.get());

        // erase this actor's components from any previous collisions
        for (auto it {m_previousComponentCollisions.begin()}; it != m_previousComponentCollisions.end();)
        {
            auto const [a, b] = *it;
            if (actorComponents.contains(a) || actorComponents.contains(b))
                it = m_previousComponentCollisions.erase(it);
            else
                ++it;
        }

        // erase this actor from any previous collisions
        for (auto it {m_previousActorCollisions.begin()}; it != m_previousActorCollisions.end();)
        {
            auto const [a, b] = *it;
            if (a == actor || b == actor)
                it = m_previousActorCollisions.erase(it);
            else
                ++it;
        }
    }
}
