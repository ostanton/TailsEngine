#ifndef TAILS_UI_STACK_PANEL_HPP
#define TAILS_UI_STACK_PANEL_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/Panel.hpp>

namespace tails::ui
{
    class CStackPanelSlot;
    
    class TAILS_API CStackPanel : public CPanel
    {
    public:
        CStackPanel();
        CStackPanel(const CStackPanel&) = delete;
        CStackPanel(CStackPanel&&) noexcept;
        CStackPanel& operator=(const CStackPanel&) = delete;
        CStackPanel& operator=(CStackPanel&&) noexcept;
        ~CStackPanel() override;

        CSlot* addChild(std::unique_ptr<CWidget> child) override;
        
        template<Derives<CWidget> WidgetT, typename... ArgsT>
        requires ConstructibleUserType<WidgetT, ArgsT...>
        CStackPanelSlot* createChildInStackPanel(ArgsT&&... args)
        {
            return addChildWithCustomSlot<CStackPanelSlot>(std::make_unique<WidgetT>(std::forward<ArgsT>(args)...));
        }
    };
}

#endif // TAILS_UI_STACK_PANEL_HPP
