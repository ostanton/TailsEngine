#include "TailsEngine/Core/ApplicationWindow.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <TailsEngine/Core/GameInstance.h>

#include "TailsEngine/Core/Viewport.h"
#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/ResourceManager.h"

tails::ApplicationWindow::ApplicationWindow()
{
    videoMode.reset(new sf::VideoMode(windowResolution.x, windowResolution.y));
    renderWindow.reset(new sf::RenderWindow(*videoMode, "Tails Engine"));
    windowEvent.reset(new sf::Event);
}

void tails::ApplicationWindow::construct()
{
    Object::construct();

    postInitSfml();
}

void tails::ApplicationWindow::postInitSfml()
{
    m_inputManager.reset(new InputManager);
    m_resourceManager.reset(new ResourceManager);
    
    gameInstance.reset(newObject<GameInstance>(this));
    gameInstance->gameView->setViewport(sf::FloatRect(sf::Vector2f(0.f, 0.f), viewResolution));
    
    viewport.reset(newObject<Viewport>(this));
    viewport->widgetView->setSize(viewResolution);

    postInitialise();
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
    
    mainLoop();
}

void tails::ApplicationWindow::mainLoop()
{
    while (renderWindow->isOpen())
    {
        // Events
        if (renderWindow->pollEvent(*windowEvent))
        {
            switch (windowEvent->type)
            {
                default:
                    break;
            case sf::Event::Closed:
                renderWindow->close();
                break;
            }

            m_inputManager->preUpdate(*windowEvent);
        }
        
        renderWindow->clear();

        gameInstance->update();

        // TODO - get these views working
        //renderWindow->setView(*gameInstance->gameView);
        renderWindow->draw(*gameInstance);
        
        //renderWindow->setView(*viewport->widgetView);
        renderWindow->draw(*viewport);

        renderWindow->display();

        m_inputManager->postUpdate();
    }
}
