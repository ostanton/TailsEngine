#include <Tails/Engine.hpp>
#include <Tails/LevelState.hpp>
#include <Tails/RectEntity.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Subsystems/Manager.hpp>
#include <Tails/Managers/Manager.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <LeksysINI/iniparser.hpp>
#include <iostream>

namespace tails
{
    Engine::Engine()
    {

    }

    Engine::~Engine()
    {

    }

    void Engine::Paths::printPaths()
    {
        std::cout
            << "Paths:\n"
            << "  Data = " << data << "\n"
            << "  Textures = " << textures << "\n"
            << "  Sounds = " << sounds << "\n"
            << "  Fonts = " << fonts << "\n"
            << "  Levels = " << levels << "\n"
            << "  Input = " << input << "\n"
            << "  Saves = " << saves << "\n";
    }

    void Engine::WindowSettings::printSettings()
    {
        std::cout << "\nWindow:\n"
            << "  Title = " << title << "\n"
            << "  Size = " << size.x << "x" << size.y << "\n"
            << "  Fullscreen = " << fullscreen << "\n";
    }

    sf::Uint32 Engine::WindowSettings::getWindowStyle()
    {
        return fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    }

    void Engine::initialise()
    {
        Debug::print("Initialising engine...\n");
        loadIni();
        initSubsystems();
        initWindow();
        setupStates();
        Debug::print("Engine initialised!\n");
    }

    void Engine::run()
    {
        Debug::print("Begin game loop.\n");
        sf::Clock clock;

        while (m_window->isOpen())
        {
            sf::Event ev;
            auto time = clock.restart();

            while (m_window->pollEvent(ev))
            {
                switch (ev.type)
                {
                    case sf::Event::Closed:
                        m_window->close();
                }
            }

            preTick();
            tick(time);
            draw();
            postTick();
        }

        Debug::print("\nEnd game loop.");
        std::cout << "  Engine was alive for: " << m_lifetime << " seconds.\n";

        deinitialise();
    }

    sf::RenderWindow& Engine::getWindow()
    {
        return *m_window;
    }

    EngineSubsystem* Engine::getSubsystem(const std::string& name)
    {
        if (!m_subsystems.contains(name)) return nullptr;

        return m_subsystems[name].get();
    }

    ManagerSubsystem& Engine::getManagerSubsystem()
    {
        return *getSubsystem<ManagerSubsystem>("manager");
    }

    void Engine::loadIni()
    {
        Debug::print("Loading engine.ini");
        INI::File engineIni;
        if (!engineIni.Load("engine.ini"))
        {
            // fails
            Debug::print("Failed to load engine.ini");
            return;
        }

        auto pathsSect = engineIni.GetSection("paths");
        if (!pathsSect)
        {
            // fails to find section
            Debug::print("Failed to get paths section");
            return;
        }

        m_paths.data = pathsSect->GetValue("data").AsString();
        m_paths.textures = pathsSect->GetValue("textures").AsString();
        m_paths.sounds = pathsSect->GetValue("sounds").AsString();
        m_paths.fonts = pathsSect->GetValue("fonts").AsString();
        m_paths.levels = pathsSect->GetValue("levels").AsString();
        m_paths.input = pathsSect->GetValue("input").AsString();
        m_paths.saves = pathsSect->GetValue("saves").AsString();

        m_paths.printPaths();

        auto renderSect = engineIni.GetSection("render");
        if (!renderSect)
        {
            Debug::print("Failed to get render section");
            return;
        }

        m_internalRes.x = renderSect->GetValue("resolution").AsArray()[0].AsDouble();
        m_internalRes.y = renderSect->GetValue("resolution").AsArray()[1].AsDouble();

        std::cout << "Render resolution = " << m_internalRes.x << "x" << m_internalRes.y << "\n";

        auto windowSect = engineIni.GetSection("window");
        if (!windowSect)
        {
            Debug::print("Failed to get window section");
            return;
        }
        m_windowSettings.title = windowSect->GetValue("title").AsString();
        m_windowSettings.size.x = windowSect->GetValue("size").AsArray()[0].AsInt();
        m_windowSettings.size.y = windowSect->GetValue("size").AsArray()[1].AsInt();
        m_windowSettings.fullscreen = windowSect->GetValue("fullscreen").AsBool();

        m_windowSettings.printSettings();

        Debug::print("engine.ini loaded!\n");
    }

    void Engine::initSubsystems()
    {
        Debug::print("Initialising engine subsystems:");
        createSubsystem<ManagerSubsystem>("manager");
        Debug::print("Engine subsystems initialised.\n");
    }

    void Engine::deinitSubsystems()
    {
        Debug::print("Deinitialising subsystems:");
        for (auto& subsystemPair : m_subsystems)
        {
            Debug::print("  Deinitialising " + subsystemPair.first + " subsystem...");
            subsystemPair.second->deinit();
            Debug::print("  " + subsystemPair.first + " subsystem deinitialised.");
        }

        Debug::print("Subsystems deinitialised.\n");

        Debug::print("Destroying subsystems...");
        m_subsystems.clear();
        Debug::print("Subsystems destroyed.\n");
    }

    void Engine::addSubsystem(const std::string& name, std::unique_ptr<EngineSubsystem> subsystem)
    {
        Debug::print("  Initialising " + name + " subsystem...");
        m_subsystems[name] = std::move(subsystem);
        m_subsystems[name]->outer = this;
        m_subsystems[name]->init();
        Debug::print("  " + name + " subsystem initialised.");
    }

    void Engine::destroySubsystem(const std::string& name)
    {
        if (!m_subsystems.contains(name)) return;

        m_subsystems[name]->pendingDestroy = true;
    }

    void Engine::initWindow()
    {
        Debug::print("Initialising window...");
        m_window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(
                m_windowSettings.size.x,
                m_windowSettings.size.y),
            m_windowSettings.title,
            m_windowSettings.getWindowStyle());
        Debug::print("Window initialised!\n");
    }

    void Engine::setupStates()
    {
        Debug::print("Setting up states:");
        m_stateStack.m_defaultCameraRes = m_internalRes;
        // TODO: work out how initial/default state is setup!
        auto levelState = m_stateStack.emplaceState<LevelState>();
        levelState->spawnEntity<RectEntity>();
        Debug::print("States setup!\n");
    }

    void Engine::preTick()
    {
        m_stateStack.preTick();

        for (auto& subsystemPair : m_subsystems)
        {
            subsystemPair.second->preTick();

            if (subsystemPair.second->pendingCreate)
                subsystemPair.second->pendingCreate = true;
        }
    }

    void Engine::tick(sf::Time& time)
    {
        m_stateStack.tick(time.asSeconds());

        m_lifetime += time.asSeconds();

        for (auto& subsystemPair : m_subsystems)
        {
            if (!subsystemPair.second->pendingCreate)
                subsystemPair.second->tick(time.asSeconds());
        }
    }

    void Engine::draw()
    {
        m_window->clear();
        m_window->draw(m_stateStack);
        m_window->display();
    }

    void Engine::postTick()
    {
        m_stateStack.postTick();

        for (auto it {m_subsystems.begin()}; it != m_subsystems.end();)
        {
            (*it).second->postTick();

            if ((*it).second->pendingDestroy)
            {
                Debug::print("  " + (*it).first + " subsystem destroyed.");
                (*it).second->deinit();
                m_subsystems.erase(it);
            }
            else
                ++it;
        }
    }

    void Engine::deinitialise()
    {
        Debug::print("\nDeinitialising engine...\n");
        m_stateStack.removeStates();
        deinitSubsystems();
        Debug::print("Engine deinitialised. Exiting...");
    }
}
