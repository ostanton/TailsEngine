#ifndef TAILS_PRIMITIVE_COMPONENT_HPP
#define TAILS_PRIMITIVE_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/ActorComponent.hpp>
#include <Tails/Renderer/RenderItem.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Maths/Rect.hpp>

namespace tails
{
    enum class ECollisionType : u8
    {
        Block,
        Overlap,
        None
    };
    
    /**
     * Actor component with a transform, optional collision, and rendering capabilities.
     * They form a tree in their owning actor.
     *
     * TODO - iterators to help iterate over the tree structure
     */
    class TAILS_API CPrimitiveComponent : public CActorComponent, public IRenderItem
    {
    public:
        void setParent(CPrimitiveComponent* parent);
        [[nodiscard]] CPrimitiveComponent* getParent() const;

        template<typename FuncT>
        void forEachChild(FuncT func, bool recursive = false);

        [[nodiscard]] virtual SFloatRect getGlobalBounds() const noexcept;

        [[nodiscard]] bool isOverlapping(const CPrimitiveComponent* other) const noexcept;
        
        STransform2D transform;
        bool visible {true};
        ECollisionType collisionType {ECollisionType::Block};
        u8 collisionMask {0};

    protected:
        void onRender(IRenderer& renderer) const override;

        void onOverlap(CPrimitiveComponent* otherComponent);

    private:
        void addChild(CPrimitiveComponent* child);
        [[nodiscard]] CPrimitiveComponent* getLastChild() const;
        
        CPrimitiveComponent* m_parent {nullptr};
        CPrimitiveComponent* m_firstChild {nullptr};
        CPrimitiveComponent* m_nextSibling {nullptr};
    };

    template <typename FuncT>
    void CPrimitiveComponent::forEachChild(FuncT func, const bool recursive)
    {
        for (auto nextChild {m_firstChild}; nextChild; nextChild = nextChild->m_nextSibling)
        {
            func(nextChild);
            
            if (recursive)
                nextChild->forEachChild(func, true);
        }
    }
}

#endif // TAILS_PRIMITIVE_COMPONENT_HPP
