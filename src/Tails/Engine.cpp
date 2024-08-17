#include <Tails/Engine.hpp>
#include <Tails/Level.hpp>
#include <Tails/Directories.hpp>
#include <Tails/EngineRegistry.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

namespace tails
{
    CEngine::CEngine() : CEngine("engine.json", {std::make_unique<CEngineRegistry>()})
    {
    }

    CEngine::CEngine(const std::string& engineSetupFile,
        std::vector<std::unique_ptr<CClassRegistry>>&& registries)
            : m_registries(std::move(registries))
    {
        if (!getRegistry<CEngineRegistry>())
            m_registries.emplace_back(std::make_unique<CEngineRegistry>());
        
        // Setup world
        m_world.outer = this;
        
        std::fstream setupFile {engineSetupFile};
        nlohmann::json setupJson {nlohmann::json::parse(setupFile)};

        if (setupJson.is_null())
        {
            // TODO - debug print fail error thing
            return;
        }

        if (const auto& dirJson = setupJson["dirs"]; !dirJson.is_null())
            CDirectories::loadDirectories(dirJson);
        
        // Set world's default level
        if (const auto& defaultLevelJson = setupJson["default_level"]; !defaultLevelJson.is_null())
            m_world.setDefaultLevel(defaultLevelJson.get<std::string>());

        if (const auto& renderJson = setupJson["render"]; !renderJson.is_null())
        {
            if (const auto& resolutionJson = renderJson["resolution"]; !resolutionJson.is_null())
                m_renderResolution = {
                    resolutionJson["x"].get<unsigned int>(),
                    resolutionJson["y"].get<unsigned int>()
                };
            
            // Setup internal render texture
            m_renderTextureInternal.create(m_renderResolution.x, m_renderResolution.y);

            // Set the size and center of the camera initially
            m_renderView.setSize(
                static_cast<float>(m_renderResolution.x),
                static_cast<float>(m_renderResolution.y)
            );
            m_renderView.setCenter(m_renderView.getSize() * 0.5f);
        }
    }

    CEngine::~CEngine() = default;

    void CEngine::run()
    {
        // Set default render target as window if it has not already been set
        if (!m_renderTarget)
            setRenderTarget<sf::RenderWindow>(
                sf::VideoMode(m_windowResolution.x, m_windowResolution.y), "Window");
        
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
            m_renderTarget->draw(sf::Sprite(internalRenderTexture));
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

    void CEngine::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
        const sf::Vector2f ratio {
            static_cast<float>(windowSize.x) / static_cast<float>(m_renderResolution.x),
            static_cast<float>(windowSize.y) / static_cast<float>(m_renderResolution.y)
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
