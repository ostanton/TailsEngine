#ifndef TAILS_COLLISION_MANAGER_HPP
#define TAILS_COLLISION_MANAGER_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Maths.hpp>
#include <Tails/Concepts.hpp>

#include <set>
#include <vector>

namespace tails
{
    class CComponent;
    class CActor;

    template<typename T>
    struct TCollisionPair
    {
        T* a;
        T* b;

        TCollisionPair(T* inA, T* inB)
            : a(maths::min(inA, inB)), b(maths::max(inA, inB))
        {}

        [[nodiscard]] constexpr auto operator<=>(const TCollisionPair&) const noexcept = default;
    };

    using SComponentCollisionPair = TCollisionPair<CComponent>;
    using SActorCollisionPair = TCollisionPair<CActor>;

    /**
     * Manages collisions within a level, tracking currently colliding components and actors
     */
    class TAILS_API CCollisionManager final
    {
    public:
        void beginCollisions();
        void endCollisions();

        void registerCollision(CComponent* compA, CComponent* compB);

        [[nodiscard]] bool hasActorCollisionStarted(CActor* actorA, CActor* actorB) const noexcept;
        void markActorCollisionStarted(CActor* actorA, CActor* actorB) noexcept;

        [[nodiscard]] bool didCollisionStart(CComponent* compA, CComponent* compB) const noexcept;
        [[nodiscard]] bool didCollisionStart(CActor* actorA, CActor* actorB) const noexcept;

        [[nodiscard]] bool areColliding(const CComponent* compA, const CComponent* compB) const noexcept;
        [[nodiscard]] bool areColliding(const CActor* actorA, const CActor* actorB) const noexcept;

        [[nodiscard]] std::vector<CComponent*> getCollisionsFor(const CComponent* component) const noexcept;
        [[nodiscard]] std::vector<CActor*> getCollisionsFor(const CActor* actor) const noexcept;

        template<Invocable<void, CComponent*, CComponent*> FuncT>
        void forEndedComponentCollisions(FuncT func) const noexcept
        {
            for (const auto& pair : m_previousComponentCollisions)
                if (!m_currentComponentCollisions.contains(pair))
                    func(pair.a, pair.b);
        }

        template<Invocable<void, CActor*, CActor*> FuncT>
        void forEndedActorCollisions(FuncT func) const noexcept
        {
            for (const auto& pair : m_previousActorCollisions)
                if (!m_currentActorCollisions.contains(pair))
                    func(pair.a, pair.b);
        }

    private:
        std::set<SComponentCollisionPair> m_currentComponentCollisions;
        std::set<SComponentCollisionPair> m_previousComponentCollisions;

        std::set<SActorCollisionPair> m_currentActorCollisions;
        std::set<SActorCollisionPair> m_previousActorCollisions;
        std::set<SActorCollisionPair> m_actorCollisionsStarted;
    };
}

#endif // TAILS_COLLISION_MANAGER_HPP
