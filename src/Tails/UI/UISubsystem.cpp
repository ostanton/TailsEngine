#include <Tails/UI/UISubsystem.hpp>
#include <Tails/UI/Widget.hpp>
#include <Tails/UI/Navigation.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails::ui
{
    CUISubsystem::CUISubsystem()
        : m_navigation(std::make_unique<CNavigation>(this))
    {
    }

    CUISubsystem::CUISubsystem(CUISubsystem&&) noexcept = default;
    CUISubsystem& CUISubsystem::operator=(CUISubsystem&&) noexcept = default;

    void CUISubsystem::init()
    {
        
    }

    CUISubsystem::~CUISubsystem() = default;

    CWidget* CUISubsystem::setRootWidgetImpl(std::unique_ptr<CWidget> widget)
    {
        widget->outer = this;
        m_rootWidget = std::move(widget);
        return m_rootWidget.get();
    }

    void CUISubsystem::preTick()
    {
        if (m_rootWidget)
            m_rootWidget->preTick();
    }

    void CUISubsystem::eventInput(const sf::Event& ev) const
    {
        if (m_rootWidget)
            m_rootWidget->eventInput(ev);

        // do things to navigation
        //m_navigation
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
