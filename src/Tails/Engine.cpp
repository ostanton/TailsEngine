#include <Tails/Engine.hpp>
#include <Tails/Level.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

namespace tails
{
    CEngine::CEngine()
    {
        // TODO - swap magic numbers with user-defined ones or something

        // Setup internal render texture
        m_renderTextureInternal.create(240, 160);

        // Set the size and center of the camera initially
        m_renderView.setSize(240.f, 160.f);
        m_renderView.setCenter(120.f, 80.f);

        // Setup world
        m_world.outer = this;
        // TODO - default level to load
        m_world.setDefaultLevel("");
    }

    CEngine::~CEngine() = default;

    void CEngine::init()
    {
        // Set default render target as window
        setRenderTarget<sf::RenderWindow>(sf::VideoMode(640, 480), "Window");
    }

    void CEngine::run()
    {
        sf::Clock clock;
        const auto window = dynamic_cast<sf::RenderWindow*>(m_renderTarget.get());
        const auto& internalRenderTexture = m_renderTextureInternal.getTexture();
        
        calculateInternalAspectRatio(m_renderTarget->getSize());
        
        while (m_running)
        {
            preTick();
            
            sf::Time time {clock.restart()};
            
            if (window)
            {
                sf::Event ev;
                while (window->pollEvent(ev))
                {
                    switch (ev.type)
                    {
                    default:
                        break;
                    case sf::Event::Closed:
                        kill();
                        break;
                    case sf::Event::Resized:
                        calculateInternalAspectRatio(window->getSize());
                        break;
                    }
                }
            }

            tick(time.asSeconds());
            
            m_renderTextureInternal.clear();
            draw(m_renderTextureInternal, m_renderStates);
            m_renderTextureInternal.display();

            m_renderTarget->clear();
            m_renderTarget->setView(m_renderView);
            sf::Sprite renderSprite {internalRenderTexture};
            m_renderTarget->draw(renderSprite);
            m_renderTarget->setView(m_renderTarget->getDefaultView());

            if (window)
            {
                window->display();
            }

            postTick();
        }
    }

    void CEngine::kill()
    {
        m_running = false;
    }

    void CEngine::preTick()
    {
        ITickable::preTick();

        m_world.preTick();
    }

    void CEngine::tick(float deltaTime)
    {
        m_world.tick(deltaTime);
    }

    void CEngine::draw(sf::RenderTarget& target, sf::RenderStates states)
    {
        target.draw(m_world, states);
    }

    void CEngine::postTick()
    {
        ITickable::postTick();

        m_world.postTick();
    }

    void CEngine::calculateInternalAspectRatio(sf::Vector2u windowSize)
    {
        // TODO - swap magic numbers with internal res
        const sf::Vector2f ratio {
            static_cast<float>(windowSize.x) / 240.f,
            static_cast<float>(windowSize.y) / 160.f
        };

        sf::FloatRect viewportRect {0.f, 0.f, 1.f, 1.f};

        if (ratio.x > ratio.y)
        {
            viewportRect.width = ratio.y / ratio.x;
            viewportRect.left = (1.f - viewportRect.width) / 2.f;
        }
        else if (ratio.x < ratio.y)
        {
            viewportRect.height = ratio.x / ratio.y;
            viewportRect.top = (1.f - viewportRect.height) / 2.f;
        }

        std::cout << "Width: " << viewportRect.width << "\n" <<
            "Height: " << viewportRect.height << "\n" <<
            "Left: " << viewportRect.left << "\n" <<
            "Top: " << viewportRect.top << "\n";
        m_renderView.setViewport(viewportRect);
    }
}
