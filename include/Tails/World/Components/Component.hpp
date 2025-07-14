#ifndef TAILS_COMPONENT_HPP
#define TAILS_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Maths/Rect.hpp>

#include <vector>

namespace tails
{
    class CActor;
    class CLevel;
    class CLevelRenderBatch;

    enum class ECollisionType : u8
    {
        Block,
        Overlap,
        None,
    };

    /**
     * Base class for actor components. They are arranged in a tree within their owning actor
     *
     * TODO - components need:
     * - Position (relative to parent, or world-space if it is the root)
     * - Rotation (^)
     * - Scale (^)
     * - Pivot (0..1 if possible (e.g. 0.5 is always centre), however that may not be possible)
     */
    class TAILS_API CComponent
    {
        friend CActor;

    public:
        CComponent() = default;
        CComponent(const CComponent&) = default;
        CComponent(CComponent&&) = default;
        CComponent& operator=(const CComponent&) = default;
        CComponent& operator=(CComponent&&) = default;
        virtual ~CComponent() = default;

        [[nodiscard]] CActor* getOwner() const noexcept;
        [[nodiscard]] CLevel* getLevel() const noexcept;

        void setParent(CComponent* parent) noexcept;
        [[nodiscard]] CComponent* getParent() const noexcept;

        /**
         * Gets this component's position in world-space. This is more efficient than
         * @code getWorldTransform().getPosition()@endcode as rotation and scale do not need
         * to be calculated
         * @return World position
         */
        [[nodiscard]] SVector2f getWorldPosition() const noexcept;
        [[nodiscard]] SFloatAngle getWorldRotation() const noexcept;
        [[nodiscard]] SVector2f getWorldScale() const noexcept;
        [[nodiscard]] STransform2D getWorldTransform() const noexcept;
        [[nodiscard]] SMatrix3f getWorldMatrix() const noexcept;

        virtual void onRender(CLevelRenderBatch& renderBatch) const;

        [[nodiscard]] virtual SFloatRect getLocalBounds() const noexcept;
        [[nodiscard]] SFloatRect getWorldBounds() const noexcept;

        /** Transform relative to parent component. If the parent, this is the world transform */
        STransform2D transform {0.f, 0.f, 1.f};
        bool visible {true};
        ECollisionType collisionType {ECollisionType::Block};

    protected:
        virtual void onInit();
        virtual void onTick(float deltaSeconds);
        virtual void onDeinit();

    private:
        void addChild(CComponent* child) noexcept;
        
        CActor* m_owner {nullptr};
        CComponent* m_parent {nullptr};
        std::vector<CComponent*> m_children;
    };
}

#endif // TAILS_COMPONENT_HPP
