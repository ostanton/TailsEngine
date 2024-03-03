#include "TailsEngine/Core/Screen.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "TailsEngine/Core/ApplicationWindow.h"
#include "TailsEngine/Core/Viewport.h"
#include "TailsEngine/Managers/Assets/AssetCache.h"

void tails::Screen::displayWidget(sf::Drawable* widgetToDisplay)
{
    m_widgetsPendingDisplay.emplace_back(widgetToDisplay);
}

void tails::Screen::create()
{
    m_assetCache.reset(new AssetCache);

    getAssetCache().loadFont("main_font", "Assets/Fonts/PixelOperatorMono.ttf");
    
    m_fpsCounter = createAndDisplayWidget<sf::Text>();
    m_fpsCounter->setFont(getAssetCache()["main_font"].getAssetData<sf::Font>());
    m_fpsCounter->setCharacterSize(32);
}

void tails::Screen::display()
{
    
}

void tails::Screen::update(float deltaTime)
{
    m_fpsCounter->setString("FPS: " + std::to_string(static_cast<unsigned long long>(1.f / deltaTime)));
}

void tails::Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i {0}; i < widgets.size(); i++)
    {
        // Add this screen's transform to the RenderStates' transform to update the "widgets"
        states.transform *= getTransform();
        target.draw(*widgets[i], states);
    }
}

void tails::Screen::remove()
{
    
}

void tails::Screen::destroy() const
{
    getViewport().destroyScreen(this);
}

void tails::Screen::setupData()
{
    if (m_widgetsPendingDisplay.empty())
        return;

    // Add pending to display widgets to main widgets vector to be updated and drawn
    for (auto& drawable : m_widgetsPendingDisplay)
    {
        widgets.emplace_back(std::move(drawable));
    }

    m_widgetsPendingDisplay.clear();
}

void tails::Screen::cleanupData()
{
    // Maybe have a map instead of vector for widgets, so we can have extra data on them in its value like
    // pending destroy or something

    // std::unordered_map<unique_ptr<sf::Drawable>, WidgetInfo> m_widgets;
    // std::unordered_map<unique_ptr<sf::Drawable>, bool> m_widgets; bool being pending destroy

    /**
     * struct WidgetInfo
     * {
     *     bool pendingDestroy {false};
     *     // Any other cool members to have here
     * }
     */
}

tails::Viewport& tails::Screen::getViewport() const
{
    return *dynamic_cast<Viewport*>(outer);
}

tails::AssetCache& tails::Screen::getAssetCache() const
{
    return *m_assetCache;
}
