#ifndef TAILS_UI_SLOT_HPP
#define TAILS_UI_SLOT_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>

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
        [[nodiscard]] CWidget* getContent() const noexcept {return m_content.get();}

    protected:
        // TODO - work out the deal with this
        /**
         * Called every time the content widget is drawn, this is used to layout and apply any visual changes
         * necessary for this slot, and furthermore the owning panel, to do its job.
         * @param index Current index of this slot in its owning panel
         * @param states States that affect the content widget
         */
        virtual void drawContent(size_t index, sf::RenderStates& states) {}

    private:
        void setContent(std::unique_ptr<CWidget> content);
        
        std::unique_ptr<CWidget> m_content {nullptr};
    };
}

#endif // TAILS_UI_SLOT_HPP
