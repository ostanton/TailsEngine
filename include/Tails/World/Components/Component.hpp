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
     * Base class for actor components. They are arranged in a tree within their owning actor
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

        void setParent(CComponent* parent) noexcept;
        [[nodiscard]] CComponent* getParent() const noexcept;

        virtual void onRender() const;

        STransform2D transform {0.f, 0.f, 1.f};
        bool visible {true};
        ECollisionType collisionType {ECollisionType::Block};

    protected:
        virtual void onInit();
        virtual void onTick(float deltaSeconds);

    private:
        void addChild(CComponent* child) noexcept;
        
        CActor* m_owner {nullptr};
        CComponent* m_parent {nullptr};
        std::vector<CComponent*> m_children;
    };
}

#endif // TAILS_COMPONENT_HPP
