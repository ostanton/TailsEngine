#include "TailsEngine/Core/Screen.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/ApplicationWindow.h"
#include "TailsEngine/Core/Viewport.h"
#include "TailsEngine/Managers/Assets/AssetCache.h"

void tails::Screen::create()
{
    m_assetCache.reset(new AssetCache);
}

void tails::Screen::display()
{
    
}

void tails::Screen::update(float deltaTime)
{
    
}

void tails::Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i {0}; i < widgets.size(); i++)
    {
        target.draw(*widgets[i]);
    }
}

void tails::Screen::remove()
{
    
}

void tails::Screen::destroy() const
{
    getViewport().destroyScreen(this);
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
