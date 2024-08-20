#include <Tails/Engine.hpp>
#include <Tails/Level.hpp>
#include <Tails/Directories.hpp>
#include <Tails/EngineRegistry.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Vector2.hpp>
#include <Tails/LevelSettings.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <nlohmann/json.hpp>

#include <fstream>

namespace tails
{
    std::string SWindowProperties::toString() const
    {
        return "Window properties:\nTitle - " + title + "\nResolution - " + SVector2u::toString(resolution);
    }

    std::string SRenderProperties::toString() const
    {
        return "Render properties:\nResolution - " + SVector2u::toString(resolution);
    }

    // removed make_unique for engine registry here because it was causing compile errors
    // to do with unique_ptr's deleted copy-constructor (I think). Couldn't fix it.
    CEngine::CEngine() : CEngine("engine.json", {})
    {
    }

    CEngine::CEngine(const std::string& engineSetupFile,
        std::vector<std::unique_ptr<CClassRegistry>>&& registries)
            : m_registries(std::move(registries))
    {
        // TODO - replace the above paramters with some SEngineSettings struct:
        /*
         * struct SEngineSettings
         * {
         *     string setupFile;
         *     registries;
         *     levelSettings;??
         * }
         *
         * And maybe a templated constructor for this? or just take in a unique_ptr?
         * so clients can derive the struct to add their own stuff. how would they use
         * that stuff? no idea lol. maybe not. Would be nice to have a custom levelsettings
         * struct though!
         */
        if (!getRegistry<CEngineRegistry>())
            m_registries.emplace_back(std::make_unique<CEngineRegistry>());
        
        // Setup world
        m_world.outer = this;
        
        CDebug::print("Loading " + engineSetupFile);

        std::ifstream setupFile {engineSetupFile};
        if (!setupFile.is_open())
        {
            CDebug::print("Failed to find " + engineSetupFile);
            initInternalRender();
            m_world.openLevel("");
            return;
        }

        nlohmann::json setupJson = nlohmann::json::parse(setupFile);

        if (setupJson.is_null())
        {
            CDebug::print("Failed to load " + engineSetupFile);
            initInternalRender();
            m_world.openLevel("");
            return;
        }

        CDebug::print(std::string("JSON is a valid ") + setupJson.type_name());

        /* DIRECTORIES */

        if (const auto& dirJson = setupJson["dirs"]; !dirJson.is_null())
            CDirectories::loadDirectories(dirJson);
        else
            CDebug::print("Failed to load directories, using default");

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

        CDebug::print(m_renderProperties.toString());
        CDebug::print();
        
        /* WORLD AND LEVEL */
        
        if (const auto& defaultLevelJson = setupJson["default_level"]; !defaultLevelJson.is_null())
            m_world.openLevel(defaultLevelJson.get<std::string>());
        else
        {
            CDebug::print("Failed to open default level, opening blank level");
            m_world.openLevel("");
        }

        if (const auto level = m_world.getLevel(0))
            CDebug::print("Opened level - " + level->getSettings().name);
        else
            CDebug::print("Created level is invalid!");
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

        CDebug::print(engineSetupFile + " loaded");
        CDebug::print();
    }

    CEngine::~CEngine()
    {
        CDebug::print("Engine destructing");
        CDebug::print("Engine alive for " + std::to_string(m_lifeTime) + " seconds");
    }

    void CEngine::run()
    {
        CDebug::print("Initialising final render target");
        // Set default render target as window if it has not already been set
        if (!m_renderTarget)
            setRenderTarget<sf::RenderWindow>(
                sf::VideoMode(
                    m_windowProperties.resolution.x,
                    m_windowProperties.resolution.y
                ),
                m_windowProperties.title
            );
        
        sf::Clock clock;
        const auto window = dynamic_cast<sf::RenderWindow*>(m_renderTarget.get());
        const auto& internalRenderTexture = m_renderTextureInternal.getTexture();
        
        calculateInternalAspectRatio(m_renderTarget->getSize());

        CDebug::print("Main loop started");
        
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

        CDebug::print("Main loop ended");
        CDebug::print();
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
        m_lifeTime += deltaTime;
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

    void CEngine::initInternalRender()
    {
        CDebug::print("Initialising internal render target");
        // Setup internal render texture
        m_renderTextureInternal.create(m_renderProperties.resolution.x, m_renderProperties.resolution.y);

        // Set the size and center of the camera initially
        m_renderView.setSize(
            static_cast<float>(m_renderProperties.resolution.x),
            static_cast<float>(m_renderProperties.resolution.y)
        );
        m_renderView.setCenter(m_renderView.getSize() * 0.5f);
    }

    void CEngine::calculateInternalAspectRatio(sf::Vector2u windowSize)
    {
        const sf::Vector2f ratio {
            static_cast<float>(windowSize.x) / static_cast<float>(m_renderProperties.resolution.x),
            static_cast<float>(windowSize.y) / static_cast<float>(m_renderProperties.resolution.y)
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
        
        m_renderView.setViewport(viewportRect);
    }
}
