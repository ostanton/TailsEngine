#ifndef TAILS_TRANSFORM_COMPONENT_HPP
#define TAILS_TRANSFORM_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/Component.hpp>
#include <Tails/Concepts.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>
#include <vector>

namespace tails
{
    class CEntity;
    
    /**
     * A component that has a transform, serving as its owning entity's transform
     */
    class TAILS_API CTransformComponent :
        public CComponent,
        public sf::Drawable,
        public sf::Transformable
    {
        friend CEntity;
        
    public:
        using ChildVector = std::vector<CTransformComponent*>;
        using ChildIterator = ChildVector::iterator;
        using ConstChildIterator = ChildVector::const_iterator;

        [[nodiscard]] virtual sf::FloatRect getLocalBounds() const;
        [[nodiscard]] sf::FloatRect getGlobalBounds() const;

        [[nodiscard]] sf::Vector2f getGlobalPosition() const;
        [[nodiscard]] sf::Angle getGlobalRotation() const;
        [[nodiscard]] sf::Vector2f getGlobalScale() const;

        void setParent(CTransformComponent* parent);
        [[nodiscard]] CTransformComponent* getParent() const {return m_parent;}

        template<Derives<CTransformComponent> T>
        [[nodiscard]] T* getChild() const
        {
            for (auto& child : m_children)
                if (auto castedChild = dynamic_cast<T*>(child))
                    return castedChild;

            return nullptr;
        }

        template<Derives<CTransformComponent> T>
        [[nodiscard]] std::vector<T*> getAllChildrenOfType(bool recursive = false) const
        {
            std::vector<T*> result;

            for (auto& child : m_children)
                if (auto castedChild = dynamic_cast<T*>(child))
                {
                    result.emplace_back(castedChild);
                    if (!recursive) continue;

                    if (child->hasChildren())
                    {
                        auto childChildren = child->getAllChildrenOfType<T>();
                        result.insert(result.end(), result.begin(), result.end());
                    }
                }

            return result;
        }

        [[nodiscard]] std::vector<CTransformComponent*> getAllChildren(bool recursive = false) const;

        [[nodiscard]] bool hasChild(CTransformComponent* child) const;
        [[nodiscard]] bool hasChildren() const;

        template<std::invocable<const std::unique_ptr<CTransformComponent>&> PredT>
        void forEachChild(PredT pred, bool recursive = false) const
        {
            for (auto& child : m_children)
            {
                pred(child);

                if (recursive && child->hasChildren())
                    child->forEachChild(pred, true);
            }
        }

    protected:
        [[nodiscard]] ChildIterator getChildIterator(CTransformComponent* child);
        [[nodiscard]] ConstChildIterator getChildIterator(CTransformComponent* child) const;

        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
    private:
        CTransformComponent* addChild(CTransformComponent* child);
        bool removeChild(CTransformComponent* child);
        
        CTransformComponent* m_parent {nullptr};
        ChildVector m_children;
    };
}

#endif // TAILS_TRANSFORM_COMPONENT_HPP
