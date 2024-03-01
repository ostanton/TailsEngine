#include "TailsEngine/Core/Screen.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/ApplicationWindow.h"
#include "TailsEngine/Core/Viewport.h"
#include "TailsEngine/Managers/ResourceManager.h"
#include "TailsEngine/Widgets/RectWidget.h"
#include "TailsEngine/Widgets/TextWidget.h"

namespace tails
{
class TextWidget;
}

void tails::Screen::create()
{
    
}

void tails::Screen::display()
{
    getResourceManager().loadFont("main_font", "Assets/Fonts/PixelOperatorMono.ttf");
    getViewport().createWidget<TextWidget>()->setFont(getResourceManager().fontManager.getAssetRef("main_font"));
    getViewport().createWidget<RectWidget>();
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

tails::Viewport& tails::Screen::getViewport() const
{
    return *dynamic_cast<Viewport*>(outer);
}
