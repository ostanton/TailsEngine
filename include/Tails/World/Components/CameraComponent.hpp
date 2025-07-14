#ifndef TAILS_CAMERA_COMPONENT_HPP
#define TAILS_CAMERA_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/Component.hpp>
#include <Tails/World/Camera.hpp>

namespace tails
{
    /**
     * Wrapper component for an SCamera object. Updates the level when it gets destroyed
     * so the level can auto-switch to another camera
     *
     * TODO - smoothing, etc. (either here or the SCamera struct, not sure)
     */
    class TAILS_API CCameraComponent : public CComponent
    {
    public:
        void activate();
        [[nodiscard]] bool isActive() const noexcept;

        SCamera camera;

    protected:
        void onTick(float deltaSeconds) override;
        void onDeinit() override;
    };
}

#endif // TAILS_CAMERA_COMPONENT_HPP
