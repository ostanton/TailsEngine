#ifndef TAILS_ACTOR_HPP
#define TAILS_ACTOR_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Templated/Bitset.hpp>
#include <Tails/Concepts.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class CLevel;
    class CComponent;
    class CLevelRenderBatch;
    class CCollisionManager;

    /**
     * Actor within a level. It is made up of components, but is still inheritable,
     * much the same way Unreal Engine's actors and components work. Its transform
     * is its root component's transform. It does not have a transform by itself
     */
    class TAILS_API CActor
    {
        friend CLevel;
        friend CCollisionManager;

    public:
        enum EFlags : u8
        {
            PendingKill = 1 << 0,
            IsVisible = 1 << 1,
        };

        CActor() = default;
        CActor(const CActor&) = delete;
        CActor(CActor&&) noexcept = default;
        CActor& operator=(const CActor&) = delete;
        CActor& operator=(CActor&&) noexcept = default;
        virtual ~CActor();

        [[nodiscard]] CLevel* getLevel() const;
        [[nodiscard]] std::weak_ptr<CLevel> getLevelWeak() const;
        [[nodiscard]] CComponent* getRootComponent() const;

        void setTransform(const STransform2D& transform);
        [[nodiscard]] STransform2D& getTransform() noexcept;
        [[nodiscard]] const STransform2D& getTransform() const noexcept;

        void setPosition(SVector2f position);
        [[nodiscard]] SVector2f getPosition() const noexcept;

        void setRotation(SFloatAngle rotation);
        [[nodiscard]] SFloatAngle getRotation() const noexcept;

        void setScale(SVector2f scale);
        [[nodiscard]] SVector2f getScale() const noexcept;

        void setVisible(bool visible);
        [[nodiscard]] bool isVisible() const noexcept;

        /**
         * Destroy ourselves
         */
        void destroy();

        void move(SVector2f offset);
        void rotate(SFloatAngle angle);
        void scale(SVector2f factor);

        /**
         * Generally use this in the constructor of this actor. Then, if the created component is a
         * CPrimitiveComponent, set its parent and, optionally, its relative transform. Assign the root
         * component to this if you want this to be the root. It should not have a parent, then.
         * @tparam T Component class
         * @return Created component
         */
        template<DerivedFrom<CComponent> T>
        T* createComponent()
        {
            return static_cast<T*>(addComponent(std::make_unique<T>()));
        }

        /**
         * Called every frame to render this actor's components
         * @param renderBatch The level's render data
         */
        void onRender(CLevelRenderBatch& renderBatch) const;

        /**
         * Tests collision between this actor and the target actor
         * @param other Actor to test collision against
         * @return True if they are colliding
         */
        [[nodiscard]] bool isCollidingWith(const CActor* other) const noexcept;
        [[nodiscard]] std::vector<CActor*> getCollidingActors() const noexcept;

        TBitset<EFlags> flags {IsVisible};
        /** The current layer this actor is on, currently only used for ordering in rendering */
        int layer {0};

    protected:
        virtual void onInitComponents();
        virtual void onSpawn();
        virtual void onTick(float deltaSeconds);
        virtual void onDespawn();

        void setRootComponent(CComponent* rootComponent);

        virtual void onStartCollision(CActor* otherActor, CComponent* otherComponent);
        virtual void onCollision(CActor* otherActor, CComponent* otherComponent);
        virtual void onEndCollision(CActor* otherActor, CComponent* otherComponent);

    private:
        CComponent* addComponent(std::unique_ptr<CComponent> component);

        std::weak_ptr<CLevel> m_owningLevel;
        // TODO - could store these somewhere else more optimally. For later, the Actor's interface for
        // its components would stay the same so it can wait for a while
        std::vector<std::unique_ptr<CComponent>> m_components;
        CComponent* m_rootComponent {nullptr};
    };
}

#endif // TAILS_ACTOR_HPP
