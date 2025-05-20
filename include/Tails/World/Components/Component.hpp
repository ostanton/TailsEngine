#ifndef TAILS_COMPONENT_HPP
#define TAILS_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Transform2D.hpp>

#include <vector>

namespace tails
{
    class CActor;

    enum class ECollisionType : u8
    {
        Block,
        Overlap,
        None
    };

    /**
     * Base interface for actor components. They are arranged in a tree within their owning actor
     */
    class TAILS_API IComponent
    {
        friend CActor;
        
    public:
        IComponent() = default;
        IComponent(const IComponent&) = default;
        IComponent(IComponent&&) = default;
        IComponent& operator=(const IComponent&) = default;
        IComponent& operator=(IComponent&&) = default;
        virtual ~IComponent() = default;

        [[nodiscard]] CActor* getOwner() const noexcept;

        void setParent(IComponent* parent) noexcept;
        [[nodiscard]] IComponent* getParent() const noexcept;

        virtual void onRender() const;

        STransform2D transform {0.f, 0.f, 1.f};
        bool visible {true};
        ECollisionType collisionType {ECollisionType::Block};

    protected:
        virtual void onInit();
        virtual void onTick(float deltaSeconds) = 0;

    private:
        void addChild(IComponent* child) noexcept;
        
        CActor* m_owner {nullptr};
        IComponent* m_parent {nullptr};
        std::vector<IComponent*> m_children;
    };
}

#endif // TAILS_COMPONENT_HPP
