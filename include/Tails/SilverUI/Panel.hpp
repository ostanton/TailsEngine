#ifndef TAILS_PANEL_WIDGET_HPP
#define TAILS_PANEL_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/SilverUI/Widget.hpp>
#include <Tails/SilverUI/Slot.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class TAILS_API SPanel : public SWidget
    {
    public:
        SPanel() = default;
        SPanel(const SPanel&) = delete;
        SPanel(SPanel&&) = default;
        SPanel& operator=(const SPanel&) = delete;
        SPanel& operator=(SPanel&&) = default;
        ~SPanel() override;
        
        template<typename T>
        ISlot* addChild()
        {
            return addChild(std::make_shared<T>());
        }
        
        ISlot* addChild(std::shared_ptr<SWidget> content);

        void onTick(float deltaSeconds) override;
        
    protected:
        void onRender(IRenderer& renderer) const override;
        
        virtual std::unique_ptr<ISlot> makeSlot(std::shared_ptr<SWidget> content) = 0;
        
        std::vector<std::unique_ptr<ISlot>> m_slots;
    };
}

#endif // TAILS_PANEL_WIDGET_HPP
