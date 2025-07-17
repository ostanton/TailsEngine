#ifndef TAILS_CAMERA_COMPONENT_HPP
#define TAILS_CAMERA_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/Component.hpp>
#include <Tails/World/Camera.hpp>

namespace tails
{
    /**
     * Wrapper component for an SCamera object. Allows for camera lag/smoothing and
     * updates the level when it gets destroyed so the level can auto-switch to another camera
     */
    class TAILS_API CCameraComponent : public CComponent
    {
    public:
        CCameraComponent();

        void activate();
        [[nodiscard]] bool isActive() const noexcept;

        SCamera camera;

        /** Inherit the component's position or not */
        bool inheritPosition {true};
        /** Inherit the component's rotation or not */
        bool inheritRotation {true};
        /** Inherit the component's scale or not */
        bool inheritScale {false};

        /** Whether to lag and smooth the camera position */
        bool enableLag {false};
        /** How fast should the camera lag (smaller = slower) */
        float lagSpeed {10.f};

    protected:
        void onInit() override;
        void onTick(float deltaSeconds) override;
        void onDeinit() override;

        /** The target position for the camera with current lag */
        SVector2f m_targetPosition;
    };
}

#endif // TAILS_CAMERA_COMPONENT_HPP
