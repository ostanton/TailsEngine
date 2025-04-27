#ifndef TAILS_ACTOR_COMPONENT_HPP
#define TAILS_ACTOR_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/Component.hpp>

namespace tails
{
    class CActor;

    /**
     * Default implementation of IComponent interface
     */
    class TAILS_API CActorComponent final : public IComponent
    {
        void onTick(float deltaSeconds) override;
    };
}

#endif // TAILS_ACTOR_COMPONENT_HPP
