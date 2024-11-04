#ifndef TAILS_UI_NAVIGATION_HPP
#define TAILS_UI_NAVIGATION_HPP

#include <Tails/Config.hpp>

namespace tails::ui
{
    class CUIManager;
    
    /**
     * Dictates how focus moves around.
     * TODO - implement
     */
    class TAILS_API CNavigation
    {
    public:
        CNavigation() = delete;
        explicit CNavigation(CUIManager* manager);

        [[nodiscard]] CUIManager& getUIManager() noexcept {return *m_uiManager;}
        [[nodiscard]] const CUIManager& getUIManager() const noexcept {return *m_uiManager;}

    private:
        CUIManager* m_uiManager {nullptr};
    };
}

#endif // TAILS_UI_NAVIGATION_HPP
