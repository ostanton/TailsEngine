#ifndef TAILS_UI_SLOT_HPP
#define TAILS_UI_SLOT_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/UI/SlottedWidget.hpp>

#include <memory>

namespace sf
{
    struct RenderStates;
}

namespace tails::ui
{
    class CWidget;
    class CPanel;

    /**
     * Slots do not need to preTick, tick, or postTick. Those go straight to their content (if valid).
     * 
     * A slot's purpose is to arrange its content correctly in accordance to other slots' contents within
     * a panel widget.
     */
    class TAILS_API CSlot : public CObject
    {
        friend CPanel;
        
    public:
        CSlot();
        CSlot(const CSlot&) = delete;
        CSlot(CSlot&&) noexcept;
        CSlot& operator=(const CSlot&) = delete;
        CSlot& operator=(CSlot&&) noexcept;
        ~CSlot() override;
        
        [[nodiscard]] CPanel* getOwner() const;
        [[nodiscard]] CWidget* getContent() const noexcept {return m_slottedWidget.get();}

        [[nodiscard]] sf::Vector2f getContentPosition() const;
        [[nodiscard]] sf::Angle getContentRotation() const;
        [[nodiscard]] sf::Vector2f getContentScale() const;
        [[nodiscard]] const sf::Transform& getContentTransform() const;
        [[nodiscard]] const sf::Transform& getContentInverseTransform() const;

        /**
         * Aggregate of content widget local bounds, and any padding, etc. that is added on top
         * @return Bounding rect
         */
        [[nodiscard]] virtual sf::FloatRect getLocalBounds() const;

    protected:
        // TODO - work out the deal with this
        /**
         * Called every time the content widget is drawn, this is used to layout and apply any visual changes
         * necessary for this slot, and furthermore the owning panel, to do its job.
         * @param index Current index of this slot in its owning panel
         * @param states States that affect the content widget
         */
        virtual void drawContent(size_t index, sf::RenderStates& states);

        SSlottedWidget* getSlottedWidgetAtIndex(size_t index) const;

        SSlottedWidget m_slottedWidget;
        
    private:
        void setContent(std::unique_ptr<CWidget> content);
    };
}

#endif // TAILS_UI_SLOT_HPP
