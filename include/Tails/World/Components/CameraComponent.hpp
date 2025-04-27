#ifndef TAILS_CAMERA_COMPONENT_HPP
#define TAILS_CAMERA_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/Component.hpp>
#include <Tails/Maths/Rect.hpp>

namespace tails
{
    /**
     * Used as a view in a level
     *
     * TODO - offscreen rendering? Really doesn't need to be its own component does it?
     */
    class TAILS_API CCameraComponent : public IComponent
    {
    public:
        void activate();
        [[nodiscard]] bool isActive() const noexcept;
        
        SFloatRect bounds;

    protected:
        void onTick(float deltaSeconds) override;
    };
}

#endif // TAILS_CAMERA_COMPONENT_HPP
