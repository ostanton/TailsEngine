#include "TailsEngine/Core/ApplicationWindow.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <TailsEngine/Core/GameInstance.h>

#include "TailsEngine/Core/Viewport.h"
#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

tails::ApplicationWindow::ApplicationWindow()
{
    videoMode = std::make_unique<sf::VideoMode>(windowResolution.x, windowResolution.y);
    renderWindow = std::make_unique<sf::RenderWindow>(*videoMode, windowTitle);
    windowView.reset(sf::FloatRect(0.f, 0.f,
        static_cast<float>(viewResolution.x),
        static_cast<float>(viewResolution.y)));
    
    renderTexture.create(viewResolution.x + 1, viewResolution.y + 1);
    renderTexture.setSmooth(false);
    renderSprite.setTexture(renderTexture.getTexture());
}

void tails::ApplicationWindow::construct()
{
    Object::construct();

    postInitSfml();
    initWindowSettings();
    postInitialise();
}

void tails::ApplicationWindow::postInitSfml()
{
    gameInstance = newObjectUnique<GameInstance>(this);
    gameInstance->gameView.reset({0.f, 0.f,
        static_cast<float>(viewResolution.x),
        static_cast<float>(viewResolution.y)
    });
    
    viewport = newObjectUnique<Viewport>(this);
    viewport->widgetView.reset({0.f, 0.f,
        static_cast<float>(viewResolution.x),
        static_cast<float>(viewResolution.y)
    });

    //calculateAspectRatio(renderTexture.getSize());
}

void tails::ApplicationWindow::initWindowSettings()
{
    renderWindow->setFramerateLimit(60);

    m_assetCache.loadTexture("icon", "Assets/Textures/Tails.png");
    renderWindow->setIcon(64, 64,
        m_assetCache["icon"].getAssetData<sf::Texture>().copyToImage().getPixelsPtr());
}

void tails::ApplicationWindow::postInitialise()
{
    /**
     * The point of create() is to give the initialisation of members over to the constructor and construct() methods.
     * SFML classes are initialised in the constructors, TailsEngine classes are initialised in the construct() methods.
     * create() therefore is a place where we can be certain that any member from our outer is initialised and will
     * not be null or fail.
     *
     * Constructors initialises (allocate memory) to SFML classes
     * construct() initialises (allocate memory) to TailsEngine classes
     * create() does not initialisation, it can use whatever member it wants
     *
     * Because of this, the viewport should have no problem accessing members from gameInstance even though
     * gameInstance's create() is called after viewport's
     */
    viewport->create();
    gameInstance->create();
}

void tails::ApplicationWindow::setupData()
{
    viewport->setupData();
    gameInstance->setupData();
}

void tails::ApplicationWindow::mainLoop()
{
    while (renderWindow->isOpen())
    {
        setupData();
        
        globalTime = globalClock.restart();
        
        // Events
        if (renderWindow->pollEvent(windowEvent))
        {
            switch (windowEvent.type)
            {
            default:
                break;
            case sf::Event::Closed:
                renderWindow->close();
                break;
            case sf::Event::Resized:
                calculateAspectRatio(windowEvent.size.width, windowEvent.size.height);
                break;
            }

            m_inputManager.preUpdate(windowEvent);
        }

        // Call outside poll event but still send through the event itself
        switch (m_inputMode)
        {
        case InputMode::Game:
            gameInstance->processInput(windowEvent);
            break;
        case InputMode::Viewport:
            viewport->processInput(windowEvent);
            break;
        case InputMode::GameAndViewport:
            gameInstance->processInput(windowEvent);
            viewport->processInput(windowEvent);
            break;
        }
        
        renderTexture.clear();

        gameInstance->update();
        viewport->update();

        renderTexture.setView(gameInstance->gameView);
        renderTexture.draw(*gameInstance);
        
        renderTexture.setView(viewport->widgetView);
        renderTexture.draw(*viewport);

        renderTexture.setView(renderTexture.getDefaultView());

        renderTexture.display();
        renderSprite.setTexture(renderTexture.getTexture());

        renderWindow->clear();
        renderWindow->setView(windowView);
        renderWindow->draw(renderSprite);
        renderWindow->setView(renderWindow->getDefaultView());
        renderWindow->display();

        m_inputManager.postUpdate();

        cleanupData();
    }
}

void tails::ApplicationWindow::cleanupData()
{
    viewport->cleanupData();
    gameInstance->cleanupData();

    m_inputMode = targetInputMode;
}

void tails::ApplicationWindow::calculateAspectRatio(unsigned width, unsigned height)
{
    sf::FloatRect viewportRect {0.f, 0.f, 1.f, 1.f};
    
    const float winWidth {static_cast<float>(width)};
    const float winHeight {static_cast<float>(height)};

    const float ratioX {winWidth / static_cast<float>(viewResolution.x)};
    const float ratioY {winHeight / static_cast<float>(viewResolution.y)};

    if (ratioX > ratioY)
    {
        viewportRect.width = ratioY / ratioX;
        viewportRect.left = (1.f - viewportRect.width) / 2.f;
    }
    else if (ratioX < ratioY)
    {
        viewportRect.height = ratioX / ratioY;
        viewportRect.top = (1.f - viewportRect.height) / 2.f;
    }
    
    //gameInstance->gameView.setViewport(viewportRect);
    //viewport->widgetView.setViewport(viewportRect);
    windowView.setViewport(viewportRect);
}

void tails::ApplicationWindow::calculateAspectRatio(const sf::Vector2u& size)
{
    calculateAspectRatio(size.x, size.y);
}
