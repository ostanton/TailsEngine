#ifndef TAILS_ACTOR_HPP
#define TAILS_ACTOR_HPP

#include <Tails/Core.hpp>
#include <Tails/Renderer/RenderItem.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Templated/Bitset.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class CLevel;
    class CLayer;
    class CActorComponent;
    class CPrimitiveComponent;

    /**
     * Actor within a level. It is made up of components, but is still inheritable,
     * much the same way Unreal Engine's actors and components work. Its transform
     * is its root component's transform. It does not have a transform by itself
     * 
     * TODO - batch render these somehow. Get their underlying SDL structures maybe
     */
    class TAILS_API CActor : IRenderItem
    {
        friend CLevel;
        friend CLayer;
        
    public:
        enum EFlags : u8
        {
            PendingKill = 1 << 0
        };
        
        CActor() = default;
        CActor(const CActor&) = delete;
        CActor(CActor&&) noexcept = default;
        CActor& operator=(const CActor&) = delete;
        CActor& operator=(CActor&&) noexcept = default;
        ~CActor() override;
        
        [[nodiscard]] CLevel* getLevel() const;
        [[nodiscard]] CPrimitiveComponent* getRootComponent() const;

        void setTransform(const STransform2D& transform);
        [[nodiscard]] const STransform2D& getTransform() const;

        void setPosition(SVector2f position);
        [[nodiscard]] SVector2f getPosition() const;

        void setRotation(float rotation);
        [[nodiscard]] float getRotation() const;

        void setScale(SVector2f scale);
        [[nodiscard]] SVector2f getScale() const;

        /**
         * Destroy ourself
         */
        void destroy() const;
        
        void move(SVector2f offset);

        [[nodiscard]] bool isOverlapping(const CActor* other) const noexcept;

        /**
         * Generally use this in the constructor of this actor. Then, if the created component is a
         * CPrimitiveComponent, set its parent and, optionally, its relative transform. Assign the root
         * component to this if you want this to be the root. It should not have a parent, then.
         * @tparam T Component class
         * @return Created component
         */
        template<typename T>
        T* createComponent()
        {
            return static_cast<T*>(addComponent(std::make_unique<T>()));
        }

        void setLayer(int layer);
        [[nodiscard]] int getLayer() const noexcept;

        TBitset<EFlags> flags;

    protected:
        virtual void onInitComponents();
        virtual void onSpawn();
        virtual void onTick(float deltaSeconds);

        void setRootComponent(CPrimitiveComponent* rootComponent);

        virtual void onOverlap(CActor* otherActor);
        
    private:
        void onRender(IRenderer& renderer) const final;
        
        CActorComponent* addComponent(std::unique_ptr<CActorComponent> component);
        
        CLevel* m_owningLevel {nullptr};
        // TODO - could store these somewhere else more optimally. For later, the Actor's interface for
        // its components would stay the same so it can wait for a while
        std::vector<std::unique_ptr<CActorComponent>> m_components;
        CPrimitiveComponent* m_rootComponent {nullptr};
        /** The current layer this actor is on */
        int m_layer {0};
    };
}

#endif // TAILS_ACTOR_HPP
