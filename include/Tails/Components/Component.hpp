#ifndef TAILS_COMPONENT_HPP
#define TAILS_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Concepts.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class CEntity;

    /**
     * Base class for entity components.
     */
    class TAILS_API CComponent :
        public CObject,
        public ITickable,
        public sf::Drawable,
        public sf::Transformable
    {
        friend CEntity;
        
    public:
        using ChildVector = std::vector<std::unique_ptr<CComponent>>;
        using ChildIterator = ChildVector::iterator;
        using ConstChildIterator = ChildVector::const_iterator;
        
        [[nodiscard]] virtual sf::FloatRect getGlobalBounds() const {return {};}

        [[nodiscard]] CEntity& getOwningEntity() const;

        [[nodiscard]] sf::Vector2f getGlobalPosition() const;
        [[nodiscard]] sf::Angle getGlobalRotation() const;
        [[nodiscard]] sf::Vector2f getGlobalScale() const;

        template<Derives<CComponent> T, typename... ArgsT>
        T* createChild(ArgsT&&... args)
        {
            return static_cast<T*>(addChild(std::unique_ptr<T>(newObject<T>(outer, std::forward<ArgsT>(args)...))));
        }

        template<Derives<CComponent> T>
        T* createRegisteredChild(std::string_view className)
        {
            return static_cast<T*>(addChild(std::unique_ptr<T>(newObject<T>(className, outer))));
        }

        CComponent* createRegisteredComponent(std::string_view className);

        template<Derives<CComponent> T>
        [[nodiscard]] T* getChild() const
        {
            for (auto& child : m_children)
                if (auto castedChild = dynamic_cast<T*>(child.get()))
                    return castedChild;

            return nullptr;
        }

        template<Derives<CComponent> T>
        [[nodiscard]] std::vector<T*> getAllChildrenOfType(bool recursive = false) const
        {
            std::vector<T*> result;

            for (auto& child : m_children)
                if (auto castedChild = dynamic_cast<T*>(child.get()))
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

        [[nodiscard]] std::vector<CComponent*> getAllChildren(bool recursive = false) const;
        
        void destroyChild(CComponent* child, bool recursive = true);

        [[nodiscard]] bool hasChild(CComponent* child) const;
        [[nodiscard]] bool hasChildren() const;

        [[nodiscard]] CComponent* getParent() const {return m_parent;}

        template<std::invocable<const std::unique_ptr<CComponent>&> PredT>
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
        virtual void create() {}
        virtual void postCreate() {}
        virtual void destroy() {}

        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        [[nodiscard]] ChildIterator getChildIterator(CComponent* child);
        [[nodiscard]] ConstChildIterator getChildIterator(CComponent* child) const;

    private:
        CComponent* addChild(std::unique_ptr<CComponent> child);
        
        CComponent* m_parent {nullptr};
        ChildVector m_children;
    };
}

#endif // TAILS_COMPONENT_HPP
