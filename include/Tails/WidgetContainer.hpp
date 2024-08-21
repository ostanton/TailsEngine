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
        void destroyChild(CWidget* child);

    protected:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

    private:
        ChildVector m_children;
    };
}

#endif // TAILS_WIDGETCONTAINER_HPP
