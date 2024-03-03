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
    gameInstance->gameView.setViewport(sf::FloatRect(sf::Vector2f(0.f, 0.f), viewResolution));
    
    viewport = newObjectUnique<Viewport>(this);
    viewport->widgetView.setSize(viewResolution);
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
            }

            m_inputManager.preUpdate(windowEvent);
        }

        // Call outside poll event but still send through the event itself
        gameInstance->processInput(windowEvent);
        
        renderWindow->clear();

        gameInstance->update();
        viewport->update();

        // TODO - get these views working
        //renderWindow->setView(*gameInstance->gameView);
        renderWindow->draw(*gameInstance);
        
        //renderWindow->setView(*viewport->widgetView);
        renderWindow->draw(*viewport);

        renderWindow->display();

        m_inputManager.postUpdate();

        cleanupData();
    }
}

void tails::ApplicationWindow::cleanupData()
{
    viewport->cleanupData();
    gameInstance->cleanupData();
}
