#include <Tails/Engine.hpp>
#include <Tails/Level.hpp>
#include <Tails/Directories.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Vector2.hpp>
#include <Tails/LevelSettings.hpp>
#include <Tails/EngineSettings.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <nlohmann/json.hpp>

#include <fstream>

namespace tails
{
    std::string SWindowProperties::toString() const
    {
        return "Window properties:\n  Title - \"" + title + "\"\n  Resolution - " + SVector2u::toString(resolution);
    }

    std::string SRenderProperties::toString() const
    {
        return "Render properties:\n  Resolution - " + SVector2u::toString(resolution);
    }

    CEngine::CEngine() : CEngine(std::make_unique<SEngineSettings>())
    {
    }

    CEngine::CEngine(std::unique_ptr<SEngineSettings> engineSettings)
            : m_settings(std::move(engineSettings))
    {
        CDebug::print("Initialising Engine");
        
        // engine should not be pending create
        unmarkForCreate();
        
        // If input engine settings is null, use default
        if (!m_settings)
            m_settings = std::make_unique<SEngineSettings>();
        
        // Setup world
        m_world.outer = this;
        
        CDebug::print("Loading ", m_settings->getSetupFilePath());

        std::ifstream setupFile {m_settings->getSetupFilePath()};
        if (!setupFile.is_open())
        {
            CDebug::print("Failed to find ", m_settings->getSetupFilePath());
            initMembers();
            return;
        }

        nlohmann::json setupJson = nlohmann::json::parse(setupFile);

        if (setupJson.is_null())
        {
            CDebug::print("Failed to load ", m_settings->getSetupFilePath());
            initMembers();
            return;
        }

        CDebug::print(std::string("JSON is a valid "), setupJson.type_name());
        CDebug::print();

        /* DIRECTORIES */

        if (const auto& dirJson = setupJson["directories"]; !dirJson.is_null())
            CDirectories::loadDirectories(dirJson);
        else
            CDebug::print("Failed to load directories, using default");
        CDebug::print();

        /* RENDER SETTINGS */

        if (const auto& renderJson = setupJson["render"]; !renderJson.is_null())
        {
            if (const auto& resolutionJson = renderJson["resolution"]; !resolutionJson.is_null())
                m_renderProperties.resolution = {
                    resolutionJson["x"].get<unsigned int>(),
                    resolutionJson["y"].get<unsigned int>()
                };
            else
                CDebug::print("Failed to load render resolution, using default");
        }
        else
        {
            CDebug::print("Failed to load render settings, using default");
        }

        initInternalRender();
        
        /* WORLD AND LEVEL */
        
        if (const auto& defaultLevelJson = setupJson["default_level"]; !defaultLevelJson.is_null())
            initWorldLevel(defaultLevelJson.get<std::string>());
        else
        {
            CDebug::print("Failed to open default level, opening blank level");
            initWorldLevel("");
        }

        if (const auto level = m_world.getLevel(0))
            CDebug::print("  Opened level - \"", level->getSettings().name, "\"");
        else
            CDebug::error("Created level is invalid!");
        CDebug::print();

        /* WINDOW SETTINGS */

        if (const auto& windowJson = setupJson["window"]; !windowJson.is_null())
        {
            if (const auto& titleJson = windowJson["title"]; !titleJson.is_null())
                m_windowProperties.title = titleJson.get<std::string>();
            else
                CDebug::print("Failed to load window title, using default");

            // TODO - change this for some user settings json?
            if (const auto& sizeJson = windowJson["resolution"]; !sizeJson.is_null())
            {
                m_windowProperties.resolution.x = sizeJson["x"].get<unsigned int>();
                m_windowProperties.resolution.y = sizeJson["y"].get<unsigned int>();
            }
            else
                CDebug::print("Failed to load window resolution, using default");
        }
        else
            CDebug::print("Failed to load window settings, using default");
        
        CDebug::print(m_windowProperties.toString());
        CDebug::print();

        CDebug::print(m_settings->getSetupFilePath(), " loaded");
        CDebug::print();
    }

    CEngine::CEngine(CEngine&&) noexcept = default;
    CEngine& CEngine::operator=(CEngine&&) noexcept = default;
    
    CEngine::~CEngine()
    {
        CDebug::print("Engine destructing");
        CDebug::print("Engine alive for ", m_lifeTime, " seconds");
    }

    void CEngine::run()
    {
        CDebug::print("Initialising final render target");
        // Set default render target as window if it has not already been set
        if (!m_renderTarget)
            setRenderTarget<sf::RenderWindow>(
                sf::VideoMode({
                    m_windowProperties.resolution.x,
                    m_windowProperties.resolution.y
                }),
                m_windowProperties.title
            );
        CDebug::print();
        
        sf::Clock clock;
        const auto window = dynamic_cast<sf::RenderWindow*>(m_renderTarget.get());
        if (window)
        {
            window->setFramerateLimit(m_settings->framerateLimit);
        }
        
        const auto& internalRenderTexture = m_renderTextureInternal.getTexture();
        
        calculateInternalAspectRatio(m_renderTarget->getSize());

        CDebug::print("Main loop started");
        
        while (m_running)
        {
            preTick();
            
            sf::Time time {clock.restart()};
            
            if (window)
            {
                while (const auto ev = window->pollEvent())
                {
                    m_uiManager.eventInput(ev.value());
                    
                    if (ev->is<sf::Event::Closed>())
                    {
                        kill();
                    }
                    else if (const auto* resize = ev->getIf<sf::Event::Resized>())
                    {
                        calculateInternalAspectRatio(resize->size);
                        CDebug::print("Resized window size: ", resize->size.x, "x", resize->size.y);
                    }
                }
            }

            tick(time.asSeconds());
            
            m_renderTextureInternal.clear(m_renderTextureInternalClearColour);
            draw(m_renderTextureInternal, m_renderStates);
            m_renderTextureInternal.display();

            m_renderTarget->clear(m_renderTargetClearColour);
            m_renderTarget->setView(m_renderView);
            m_renderTarget->draw(sf::Sprite(internalRenderTexture));
            m_renderTarget->setView(m_renderTarget->getDefaultView());

            if (window)
            {
                window->display();
            }

            postTick();
        }

        CDebug::print("Main loop ended");
        CDebug::print();
    }

    void CEngine::kill()
    {
        m_running = false;
    }

    void CEngine::setRenderTargetClearColour(const sf::Color colour)
    {
        m_renderTargetClearColour = colour;
    }

    void CEngine::setRenderTextureInternalClearColour(const sf::Color colour)
    {
        m_renderTextureInternalClearColour = colour;
    }

    void CEngine::preTick()
    {
        ITickable::preTick();

        m_world.preTick();
        m_uiManager.postTick();
    }

    void CEngine::tick(const float deltaTime)
    {
        m_lifeTime += deltaTime;
        m_world.tick(deltaTime);
        m_uiManager.tick(deltaTime);
    }

    void CEngine::draw(sf::RenderTarget& target, const sf::RenderStates states) const
    {
        target.draw(m_world, states);
        target.draw(m_uiManager, states);
    }

    void CEngine::postTick()
    {
        ITickable::postTick();

        m_world.postTick();
        m_uiManager.postTick();
    }

    void CEngine::initMembers()
    {
        initInternalRender();
        initWorldLevel("");
        CDebug::print(m_windowProperties.toString());
        CDebug::print();
    }

    void CEngine::initInternalRender()
    {
        CDebug::print("Initialising internal render target");
        // Setup internal render texture
        if (!m_renderTextureInternal.resize({m_renderProperties.resolution.x, m_renderProperties.resolution.y}))
            CDebug::error("Failed to resize internal render texture!");

        // Set the size and center of the camera initially
        m_renderView.setSize({
            static_cast<float>(m_renderProperties.resolution.x),
            static_cast<float>(m_renderProperties.resolution.y)
        });
        m_renderView.setCenter(m_renderView.getSize() * 0.5f);

        CDebug::print(m_renderProperties.toString());
        CDebug::print();
    }

    void CEngine::initWorldLevel(std::string path)
    {
        m_world.openLevel(std::move(path), m_settings->createLevelSettings());
    }

    void CEngine::calculateInternalAspectRatio(sf::Vector2u windowSize)
    {
        // TODO - support integer scaling so we never get half pixels on weird window sizes
        // would be nice to have a toggle so you can enable/disable for each game or even game settings?
        const sf::Vector2f ratio {
            static_cast<float>(windowSize.x) / static_cast<float>(m_renderProperties.resolution.x),
            static_cast<float>(windowSize.y) / static_cast<float>(m_renderProperties.resolution.y)
        };

        sf::FloatRect viewportRect {{0.f, 0.f}, {1.f, 1.f}};

        if (ratio.x > ratio.y)
        {
            viewportRect.size.x = ratio.y / ratio.x;
            viewportRect.position.x = (1.f - viewportRect.size.x) / 2.f;
        }
        else if (ratio.x < ratio.y)
        {
            viewportRect.size.y = ratio.x / ratio.y;
            viewportRect.position.y = (1.f - viewportRect.size.y) / 2.f;
        }
        
        m_renderView.setViewport(viewportRect);
    }
}
