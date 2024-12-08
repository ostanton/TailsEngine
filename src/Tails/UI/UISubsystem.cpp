#include <Tails/UI/UISubsystem.hpp>
#include <Tails/UI/Panel.hpp>
#include <Tails/UI/Navigation.hpp>
#include <Tails/Exception.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails::ui
{
    CUISubsystem::CUISubsystem()
        : m_rootWidget(std::make_unique<CPanel>()), m_navigation(std::make_unique<CNavigation>(this))
    {
        if (!m_rootWidget) // TODO - can this just be tested against a bad_alloc exception in the init list?
            throw CException("UI Subsystem root widget is invalid. It must be valid!");
        m_rootWidget->outer = this;
        m_focusedWidget = m_rootWidget.get();
        // should we call focusWidget() here or just silently do it?

        if (!m_navigation)
            throw CException("UI Subsystem navigation is invalid. It must be valid!");
    }

    void CUISubsystem::focusWidget(CWidget* widget)
    {
        if (m_focusedWidget == widget) return;

        if (m_focusedWidget)
            m_focusedWidget->focusLost();
        
        m_focusedWidget = widget;
        widget->focusReceived();
    }

    bool CUISubsystem::widgetFocused(const CWidget* widget) const
    {
        return m_focusedWidget == widget;
    }

    CUISubsystem::CUISubsystem(CUISubsystem&&) noexcept = default;
    CUISubsystem& CUISubsystem::operator=(CUISubsystem&&) noexcept = default;
    CUISubsystem::~CUISubsystem() = default;

    CPanel& CUISubsystem::getRootWidget() const noexcept
    {
        return *m_rootWidget;
    }

    void CUISubsystem::init()
    {
    }

    void CUISubsystem::preTick()
    {
        if (m_rootWidget)
            m_rootWidget->preTick();
    }

    void CUISubsystem::inputEvent(const sf::Event& ev)
    {
        CSubsystem::inputEvent(ev);
        
        // TODO - test for navigation keys, and move focus around. Only if input mode is UI or something though
        if (m_rootWidget)
            m_rootWidget->inputEvent(ev);
    }

    void CUISubsystem::tick(const float deltaTime)
    {
        if (m_rootWidget)
            m_rootWidget->tick(deltaTime);
    }

    void CUISubsystem::draw(sf::RenderTarget& target, const sf::RenderStates states) const
    {
        // TODO - how do we get the root widget to fill the screen? Set its states transform or something?
        if (m_rootWidget)
            target.draw(*m_rootWidget, states);
    }

    void CUISubsystem::postTick()
    {
        if (m_rootWidget)
            m_rootWidget->postTick();
    }
}
