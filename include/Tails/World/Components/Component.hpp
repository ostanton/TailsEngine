#ifndef TAILS_COMPONENT_HPP
#define TAILS_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/OrientedRect.hpp>

#include <vector>

namespace tails
{
    class CActor;
    class CLevel;
    class CLevelRenderBatch;
    struct SSATShape;

    enum class ECollisionType : u8
    {
        Block,
        Overlap,
        None,
    };

    /**
     * Base class for actor components. They are arranged in a tree within their owning actor,
     * and contain a transform local to their parent component
     */
    class TAILS_API CComponent
    {
        friend CActor;
        friend CLevel;

    public:
        CComponent() = default;
        CComponent(const CComponent&) = default;
        CComponent(CComponent&&) = default;
        CComponent& operator=(const CComponent&) = default;
        CComponent& operator=(CComponent&&) = default;
        virtual ~CComponent() = default;

        [[nodiscard]] CActor* getOwner() const noexcept;

        /**
         * Gets the layer that the owning actor is on
         * @return Owning actor's layer
         */
        [[nodiscard]] int getLayer() const noexcept;

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

        /**
         * Gets the component's local bounding rectangle as an axis-aligned bounding box
         * @return Axis-Aligned Bounding Box
         */
        [[nodiscard]] virtual SFloatRect getLocalBounds() const noexcept;

        /**
         * Gets the world bounds of this component as an oriented bounding box, including rotation
         * @return Oriented Bounding Box
         */
        [[nodiscard]] SFloatOrientedRect getWorldBounds() const noexcept;

        /**
         * Gets the world space SAT shape of this component (defaults to the world bounds if not overriden).
         * This is used for testing collisions between components
         * @return Separating Axis Theorem Shape
         */
        [[nodiscard]] virtual SSATShape getSATShape() const noexcept;

        [[nodiscard]] bool isCollidingWith(const CComponent* other) const noexcept;
        [[nodiscard]] std::vector<CComponent*> getCollidingComponents() const noexcept;

        /** Transform relative to its parent component. If the root, this is the world transform */
        STransform2D transform {0.f, 0.f, 1.f};
        bool visible {true};
        ECollisionType collisionType {ECollisionType::Block};

    protected:
        virtual void onInit();
        virtual void onTick(float deltaSeconds);
        virtual void onDeinit();

        virtual void onStartCollision(CComponent* otherComponent);
        virtual void onCollision(CComponent* otherComponent);
        virtual void onEndCollision(CComponent* otherComponent);

    private:
        void addChild(CComponent* child) noexcept;
        
        CActor* m_owner {nullptr};
        CComponent* m_parent {nullptr};
        std::vector<CComponent*> m_children;
    };
}

#endif // TAILS_COMPONENT_HPP
