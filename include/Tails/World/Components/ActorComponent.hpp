#ifndef TAILS_ACTOR_COMPONENT_HPP
#define TAILS_ACTOR_COMPONENT_HPP

#include <Tails/Core.hpp>

namespace tails
{
    class CActor;
    
    /**
     * Base component that actors are made up of
     */
    class TAILS_API CActorComponent
    {
        friend CActor;
        
    public:
        CActorComponent() = default;
        CActorComponent(const CActorComponent&) = default;
        CActorComponent(CActorComponent&&) noexcept = default;
        CActorComponent& operator=(const CActorComponent&) = default;
        CActorComponent& operator=(CActorComponent&&) noexcept = default;
        virtual ~CActorComponent() = default;
        
        [[nodiscard]] CActor* getOwningActor() const;

    protected:
        virtual void onInit();
        virtual void onTick(float deltaSeconds);
        
    private:
        CActor* m_owningActor {nullptr};
    };
}

#endif // TAILS_ACTOR_COMPONENT_HPP
