#ifndef TAILS_UI_PANEL_HPP
#define TAILS_UI_PANEL_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/Widget.hpp>
#include <Tails/Concepts.hpp>

#include <vector>

namespace tails::ui
{
    class CSlot;
    class CUISubsystem;
    
    class TAILS_API CPanel : public CWidget
    {
        friend CUISubsystem;
        
    public:
        using Container = std::vector<std::unique_ptr<CSlot>>;
        using Iterator = Container::iterator;
        using ConstIterator = Container::const_iterator;

        CPanel();
        CPanel(const CPanel&) = delete;
        CPanel(CPanel&&) noexcept;
        CPanel& operator=(const CPanel&) = delete;
        CPanel& operator=(CPanel&&) noexcept;
        ~CPanel() override;

        // TODO - this should return a pointer to the created widget, not its slot
        template<Derives<CWidget> WidgetT, typename... ArgsT>
        requires ConstructibleUserType<WidgetT, ArgsT...>
        CSlot* createChild(ArgsT&&... args)
        {
            return addChild(std::make_unique<WidgetT>(std::forward<ArgsT>(args)...));
        }

        [[nodiscard]] CWidget* getChildAt(size_t index) const;
        [[nodiscard]] constexpr bool isIndexValid(const size_t index) const noexcept {return index < m_slots.size();}
        [[nodiscard]] std::optional<size_t> getChildIndex(const CWidget* child) const;
        [[nodiscard]] std::unique_ptr<CWidget> releaseChild(size_t index) const;
        virtual CSlot* addChild(std::unique_ptr<CWidget> child);

        [[nodiscard]] sf::FloatRect getLocalBounds() const override;

    protected:
        template<Derives<CWidget> WidgetT, Derives<CSlot> SlotT>
        SlotT* createChildWithCustomSlot()
        {
            return static_cast<SlotT*>(addChildWithSlot(std::make_unique<WidgetT>(), std::make_unique<SlotT>()));
        }
        
        CSlot* addChildWithSlot(std::unique_ptr<CWidget> child, std::unique_ptr<CSlot> slot);

        template<Derives<CSlot> SlotT, typename... ArgsT>
        requires ConstructibleUserType<SlotT, ArgsT...>
        SlotT* addChildWithCustomSlot(std::unique_ptr<CWidget> child, ArgsT&&... args)
        {
            return static_cast<SlotT*>(addChildWithSlot(std::move(child), std::make_unique<SlotT>(std::forward<ArgsT>(args)...)));
        }

        void preTick() override;
        bool inputEvent(const sf::Event& ev) override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;
        
    private:
        ConstIterator getSlotIterator(CSlot* slot) const;
        ConstIterator getSlotIterator(const CWidget* child) const;
        
        Container m_slots;
    };
}

#endif // TAILS_UI_PANEL_HPP
