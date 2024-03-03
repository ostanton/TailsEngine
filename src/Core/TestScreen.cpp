#include "TailsEngine/Core/TestScreen.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "TailsEngine/Core/Viewport.h"
#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/Assets/AssetCache.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

void tails::TestScreen::display()
{
    getAssetCache().loadFont("main_font", "Assets/Fonts/PixelOperatorMono.ttf");
    
    m_textWidget = getViewport().createWidget<sf::Text>(this);
    m_textWidget->setFont(getAssetCache()["main_font"].getAssetData<sf::Font>());
    m_textWidget->setCharacterSize(16);
    
    m_rectangleShape = getViewport().createWidget<sf::RectangleShape>(this);
    m_rectangleShape->setPosition(400.f, 400.f);
    m_rectangleShape->setSize(sf::Vector2f(96.f, 48.f));
    m_rectangleShape->setFillColor(sf::Color::Blue);
}

void tails::TestScreen::update(float deltaTime)
{
    m_textWidget->setString("FPS: " + std::to_string(static_cast<unsigned long long>(1.f / deltaTime)));
    
    if (getInputManager().onActionPress("l"))
    {
        destroy();
    }
}
