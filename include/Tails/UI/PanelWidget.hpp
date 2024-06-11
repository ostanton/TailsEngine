#ifndef TAILS_PANELWIDGET_HPP
#define TAILS_PANELWIDGET_HPP

#include <Tails/UI/Widget.hpp>
#include <Tails/UI/PanelSlot.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class PanelSlot;

    class PanelWidget : public Widget
    {
    public:
        template<typename W>
        PanelSlot* addChild()
        {
            static_assert(std::is_base_of_v<Widget, W>, "Failed to add child, type does not derive Widget.");
            return addChild(std::make_unique<W>());
        }

        PanelSlot* addChild(std::unique_ptr<Widget> content);
        bool hasChild(Widget* content);
        bool removeChild(Widget* content);
        bool removeChildAt(size_t index);
        Widget* getChildAt(size_t index);
        size_t getChildIndex(Widget* content);
        size_t getChildrenCount();

    protected:
        /**
         * Adds a child using template type as slot type (internal use only)
         * @tparam S Slot type
         * @param content Content to add
         * @return Pointer to created slot
         */
        template<typename S>
        S* addChild(std::unique_ptr<Widget> content)
        {
            static_assert(std::is_base_of_v<PanelSlot, S>, "Failed to create slot, type does not derive PanelSlot.");
            content->removeFromParent();
            std::unique_ptr<PanelSlot> resultSlot {std::make_unique<S>(this, std::move(content))};
            resultSlot->getContent()->slot = resultSlot.get();
            resultSlot->getContent()->outer = outer;
            m_slots.push_back(std::move(resultSlot));
            return static_cast<S*>(m_slots.back().get());
        }

        std::vector<std::unique_ptr<PanelSlot>>::iterator getChildIterator(Widget* content);

        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

    private:
        std::vector<std::unique_ptr<PanelSlot>> m_slots;
    };
}

#endif // TAILS_PANELWIDGET_HPP
