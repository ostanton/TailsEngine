#include <Tails/Engine.hpp>
#include <Tails/Level.hpp>
#include <Tails/Directories.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Vector2.hpp>
#include <Tails/Subsystem.hpp>
#include <Tails/LevelSubsystem.hpp>
#include <Tails/UI/UISubsystem.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace tails
{
    std::ostream& operator<<(std::ostream& os, const SWindowProperties& windowProperties)
    {
        os << "Window properties:\n" <<
            "  Title - \"" << windowProperties.title << "\"\n" <<
            "  Resolution - " << SVector2u::toString(windowProperties.resolution) << "\n" <<
            "  Bits per Pixel - " << windowProperties.bitsPerPixel << "\n" <<
            "  Style - " << windowProperties.style << "\n" <<
            "  State - " << static_cast<unsigned long long>(windowProperties.state);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const SRenderProperties& renderProperties)
    {
        os << "Render properties:\n" <<
            "  Resolution - " << SVector2u::toString(renderProperties.resolution) << "\n" <<
            "  Use Internal Resolution - " << std::boolalpha << renderProperties.useInternalResolution << "\n" <<
            "  Maintain Aspect Ratio - " << renderProperties.maintainAspectRatio << std::noboolalpha;
        return os;
    }

    CEngine::CEngine()
    {
        CDebug::flush();
        CDebug::print();
        CDebug::print("Initialising Engine");
        
        // engine should not be pending create
        unmarkForCreate();
        
        setupDefaultSubsystems();

        CDebug::print("Initialising internal render target");
        // must be in constructor so m_renderView is set properly for world subsystem
        initInternalRender();
        CDebug::print("End engine constructor");
        CDebug::flush();
    }

    CEngine::CEngine(CEngine&&) noexcept = default;
    CEngine& CEngine::operator=(CEngine&&) noexcept = default;
    
    CEngine::~CEngine()
    {
        CDebug::flush();
        CDebug::print("Engine alive for ", m_lifeTime, " seconds");
        CDebug::print("Engine destructing");
    }

    CSubsystem* CEngine::getSubsystem(std::string_view id) const
    {
        const std::size_t hashed {hash(id)};
        if (!m_subsystems.contains(hashed))
        {
            CDebug::error("Failed to find ", id, " subsystem.");
            return nullptr;
        }

        return m_subsystems.at(hashed).get();
    }

    void CEngine::run()
    {
        CDebug::flush();
        initSubsystems();
        
        // Set default render target as window if it has not already been set
        if (!m_renderTarget)
            setRenderTarget<sf::RenderWindow>(
                sf::VideoMode(
                    m_windowProperties.resolution,
                    m_windowProperties.bitsPerPixel
                ),
                m_windowProperties.title,
                m_windowProperties.style,
                m_windowProperties.state
            );
        CDebug::print(m_windowProperties);
        CDebug::print();
        
        sf::Clock clock;
        const auto window = dynamic_cast<sf::RenderWindow*>(m_renderTarget.get());

        const auto& internalRenderTexture = m_renderTextureInternal.getTexture();

        calculateInternalAspectRatio(m_renderTarget->getSize());

        CDebug::print("Main loop started");
        CDebug::print("Engine render view: ", SVector2f(getRenderView().getSize()));
        
        while (m_running)
        {
            preTick();
            
            sf::Time time {clock.restart()};
            
            if (window)
            {
                while (const auto ev = window->pollEvent())
                {
                    for (const auto& subsystem : std::ranges::views::values(m_subsystems))
                        subsystem->inputEvent(ev.value());
                    
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

            if (m_renderProperties.useInternalResolution)
            {
                m_renderTextureInternal.clear(m_renderTextureInternalClearColour);
                draw(m_renderTextureInternal, m_renderStates);
                m_renderTextureInternal.display();
            }

            m_renderTarget->clear(m_renderTargetClearColour);
            m_renderTarget->setView(m_renderView);
            
            if (m_renderProperties.useInternalResolution)
                m_renderTarget->draw(sf::Sprite(internalRenderTexture));
            else
                draw(*m_renderTarget, m_renderStates);
            
            m_renderTarget->setView(m_renderTarget->getDefaultView());

            if (window)
            {
                window->display();
            }

            postTick();
        }

        CDebug::print("Main loop ended");
        CDebug::print();
        CDebug::flush();
    }

    void CEngine::kill()
    {
        m_running = false;
    }

    CLevelSubsystem& CEngine::getLevelSubsystem() const noexcept
    {
        return *getSubsystemOfType<CLevelSubsystem>();
    }

    ui::CUISubsystem& CEngine::getUISubsystem() const noexcept
    {
        return *getSubsystemOfType<ui::CUISubsystem>();
    }

    void CEngine::setRenderProperties(const SRenderProperties& properties) noexcept
    {
        m_renderProperties = properties;
        initInternalRender();
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

        for (const auto& subsystem : std::ranges::views::values(m_subsystems))
        {
            subsystem->preTick();
        }
    }

    void CEngine::tick(const float deltaTime)
    {
        m_lifeTime += deltaTime;
        
        for (const auto& subsystem : std::ranges::views::values(m_subsystems))
        {
            subsystem->tick(deltaTime);
        }
    }

    void CEngine::draw(sf::RenderTarget& target, const sf::RenderStates states) const
    {
        for (const auto& subsystem : std::ranges::views::values(m_subsystems))
        {
            target.draw(*subsystem, states);
        }
    }

    void CEngine::postTick()
    {
        ITickable::postTick();

        for (const auto& subsystem : std::ranges::views::values(m_subsystems))
        {
            subsystem->postTick();
        }
    }

    void CEngine::registerSubsystemImpl(const std::size_t id, std::unique_ptr<CSubsystem> subsystem)
    {
        subsystem->outer = this;
        m_subsystems.try_emplace(id, std::move(subsystem));
    }

    void CEngine::setupDefaultSubsystems()
    {
        CDebug::print();
        CDebug::print("Registering default subsystems");
        registerSubsystem<CLevelSubsystem>("level");
        registerSubsystem<ui::CUISubsystem>("ui");
        CDebug::print("Registered default subsystems");
        CDebug::print();
    }

    void CEngine::initSubsystems()
    {
        CDebug::print();
        CDebug::print("Initialising subsystems");
        for (const auto& subsystem : std::ranges::views::values(m_subsystems))
        {
            subsystem->init();
        }
        CDebug::print("Subsystems initialised");
        CDebug::print();
    }

    void CEngine::initInternalRender()
    {
        // Setup internal render texture
        if (!m_renderTextureInternal.resize({m_renderProperties.resolution.x, m_renderProperties.resolution.y}))
            CDebug::error("Failed to resize internal render texture!");

        // Set the size and center of the camera initially
        updateRenderView();

        CDebug::print(m_renderProperties);
        CDebug::print();
    }

    void CEngine::updateRenderView()
    {
        m_renderView.setSize({
            static_cast<float>(m_renderProperties.resolution.x),
            static_cast<float>(m_renderProperties.resolution.y)
        });
        m_renderView.setCenter(m_renderView.getSize() * 0.5f);
    }

    void CEngine::calculateInternalAspectRatio(const sf::Vector2u windowSize)
    {
        if (!m_renderProperties.maintainAspectRatio)
        {
            // TODO - doesn't work :(
            m_renderView = sf::View(sf::FloatRect({0.f, 0.f},{
                    static_cast<float>(windowSize.x),
                    static_cast<float>(windowSize.y)
            }));
            if (!m_renderTextureInternal.resize(windowSize))
            {
                CDebug::print("Failed to resize internal render target to final render target size.");
            }
            return;
        }
        
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
