#ifndef TAILS_UI_NAVIGATION_HPP
#define TAILS_UI_NAVIGATION_HPP

#include <Tails/Config.hpp>

namespace tails::ui
{
    class CUISubsystem;
    
    /**
     * Dictates how focus moves around.
     * TODO - implement
     */
    class TAILS_API CNavigation
    {
    public:
        CNavigation() = delete;
        explicit CNavigation(CUISubsystem* subsystem);

        [[nodiscard]] CUISubsystem& getUISubsystem() noexcept {return *m_uiSubsystem;}
        [[nodiscard]] const CUISubsystem& getUISubsystem() const noexcept {return *m_uiSubsystem;}

    private:
        CUISubsystem* m_uiSubsystem {nullptr};
    };
}

#endif // TAILS_UI_NAVIGATION_HPP
