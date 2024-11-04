#include <Tails/UI/UIManager.hpp>
#include <Tails/UI/Widget.hpp>
#include <Tails/UI/Navigation.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails::ui
{
    CUIManager::CUIManager()
        : m_navigation(std::make_unique<CNavigation>(this))
    {
    }

    CUIManager::CUIManager(CUIManager&&) noexcept = default;
    CUIManager& CUIManager::operator=(CUIManager&&) noexcept = default;
    CUIManager::~CUIManager() = default;

    CWidget* CUIManager::setRootWidgetImpl(std::unique_ptr<CWidget> widget)
    {
        widget->outer = this;
        m_rootWidget = std::move(widget);
        return m_rootWidget.get();
    }

    void CUIManager::preTick()
    {
        if (m_rootWidget)
            m_rootWidget->preTick();
    }

    void CUIManager::eventInput(const sf::Event& ev) const
    {
        if (m_rootWidget)
            m_rootWidget->eventInput(ev);

        // do things to navigation
        //m_navigation
    }

    void CUIManager::tick(const float deltaTime)
    {
        if (m_rootWidget)
            m_rootWidget->tick(deltaTime);
    }

    void CUIManager::draw(sf::RenderTarget& target, const sf::RenderStates states) const
    {
        // TODO - how do we get the root widget to fill the screen? Set its states transform or something?
        if (m_rootWidget)
            target.draw(*m_rootWidget, states);
    }

    void CUIManager::postTick()
    {
        if (m_rootWidget)
            m_rootWidget->postTick();
    }
}
