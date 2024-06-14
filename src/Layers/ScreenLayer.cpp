#include <Tails/Layers/ScreenLayer.hpp>
#include <Tails/UI/Widget.hpp>
#include <Tails/UI/WidgetNavigation.hpp>
#include <Tails/Assert.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    ScreenLayer::ScreenLayer() = default;
    ScreenLayer::~ScreenLayer() = default;

    Widget* ScreenLayer::setContent(std::unique_ptr<Widget> content)
    {
        content->outer = this;
        // maybe update child widget outers??
        m_content = std::move(content);
        return m_content.get();
    }

    Widget* ScreenLayer::getContent() const
    {
        return m_content.get();
    }

    std::unique_ptr<WidgetNavigation> ScreenLayer::setupWidgetNavigation()
    {
        return std::make_unique<WidgetNavigation>();
    }

    WidgetNavigation& ScreenLayer::getNavigation()
    {
        return *m_navigation;
    }

    void ScreenLayer::init(State& state)
    {
        Layer::init(state);

        m_navigation = setupWidgetNavigation();
        TailsAssert(m_navigation, "WidgetNavigation object is invalid!");
    }

    void ScreenLayer::preTick()
    {
        if (m_content)
            m_content->preTick();
    }

    void ScreenLayer::tick(float deltaTime)
    {
        if (m_content)
            m_content->tick(deltaTime);
    }

    void ScreenLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (m_content)
            target.draw(*m_content, states);
    }

    void ScreenLayer::postTick()
    {
        if (m_content)
            m_content->postTick();
    }
}
