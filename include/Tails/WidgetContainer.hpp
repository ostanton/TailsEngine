#ifndef TAILS_WIDGETCONTAINER_HPP
#define TAILS_WIDGETCONTAINER_HPP

#include <Tails/Config.hpp>
#include <Tails/Widget.hpp>

#include <vector>
#include <memory>
#include <optional>

namespace tails
{
    class CEngine;

    /**
     * Base class for containers that hold and position child widgets.
     * Probably interchangable with "panel".
     */
    class TAILS_API WContainer : public CWidget
    {
        friend CEngine;

    public:
        using ChildVector = std::vector<std::unique_ptr<CWidget>>;

        template<typename T>
        T* createChild()
        {
            static_assert(std::is_base_of_v<CWidget, T>,
                          "Failed to create child, it does not derive CWidget");

            return static_cast<T*>(addChild(std::make_unique<T>()));
        }

        CWidget* addChild(std::unique_ptr<CWidget> widget);
        [[nodiscard]] CWidget* getChildAt(size_t index) const;
        [[nodiscard]] std::optional<size_t> getChildIndex(CWidget* child) const;
        [[nodiscard]] ChildVector::const_iterator getChildIterator(CWidget* child) const;
        [[nodiscard]] size_t getChildCount() const {return m_children.size();}

        template<typename T>
        T* getChildOfClass()
        {
            static_assert(std::is_base_of_v<CWidget, T>,
                          "Failed to get child, target type does not derive CWidget");

            for (auto& child : m_children)
            {
                if (auto castedChild = dynamic_cast<T*>(child.get()))
                    return castedChild;
            }

            return nullptr;
        }

        void destroyChild(CWidget* child);

        const std::vector<std::unique_ptr<CWidget>>& getChildren() const {return m_children;}

    protected:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void drawChild(size_t childIndex) const = 0;
        void postTick() override;

    private:
        ChildVector m_children;
    };
}

#endif // TAILS_WIDGETCONTAINER_HPP
