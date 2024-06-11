#include <Tails/Engine.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Subsystems/AssetSubsystem.hpp>
#include <Tails/Subsystems/AudioSubsystem.hpp>
#include <Tails/Subsystems/RegistrySubsystem.hpp>
#include <Tails/Registries/Registry.hpp>
#include <Tails/Subsystems/InputSubsystem.hpp>
#include <Tails/Subsystems/StateSubsystem.hpp>

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

    void Engine::Paths::printPaths() const
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

    void Engine::RenderSettings::printSettings() const
    {
        std::cout << "\nRender:\n"
            << "  Resolution = " << size.x << "x" << size.y << "\n";
    }

    void Engine::WindowSettings::printSettings() const
    {
        std::cout << "\nWindow:\n"
            << "  Title = " << title << "\n"
            << "  Size = " << size.x << "x" << size.y << "\n"
            << "  Fullscreen = " << fullscreen << "\n";
    }

    sf::Uint32 Engine::WindowSettings::getWindowStyle() const
    {
        return fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    }

    void Engine::initialise()
    {
        Debug::print("Initialising engine...\n");
        loadIni();
        initSubsystems();
        Debug::print("Engine subsystems initialised.\n");
        initWindow();
        Debug::print("Window initialised!\n");
        Debug::print("Engine initialised!\n");
    }

    void Engine::run()
    {
        Debug::print("Begin game loop.\n");
        sf::Clock clock;

        while (m_window->isOpen())
        {
            preTick();

            sf::Event ev;
            auto time = clock.restart();

            while (m_window->pollEvent(ev))
            {
                switch (ev.type)
                {
                    default:
                        break;
                    case sf::Event::Closed:
                        m_window->close();
                }
            }

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

    Subsystem* Engine::getSubsystem(const std::string& name)
    {
        if (!m_subsystems.contains(name)) return nullptr;

        return m_subsystems[name].get();
    }

    AssetSubsystem& Engine::getAssetSubsystem()
    {
        return *getSubsystem<AssetSubsystem>("asset");
    }

    AudioSubsystem& Engine::getAudioSubsystem()
    {
        return *getSubsystem<AudioSubsystem>("audio");
    }

    RegistrySubsystem& Engine::getRegistrySubsystem()
    {
        return *getSubsystem<RegistrySubsystem>("m_registry");
    }

    InputSubsystem& Engine::getInputSubsystem()
    {
        return *getSubsystem<InputSubsystem>("input");
    }

    StateSubsystem& Engine::getStateSubsystem()
    {
        return *getSubsystem<StateSubsystem>("state");
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

        m_renderSettings.size.x = static_cast<float>(renderSect->GetValue("resolution").AsArray()[0].AsDouble());
        m_renderSettings.size.y = static_cast<float>(renderSect->GetValue("resolution").AsArray()[1].AsDouble());

        m_renderSettings.printSettings();

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
        createSubsystem<AssetSubsystem>("asset");
        createSubsystem<AudioSubsystem>("audio");
        createSubsystem<RegistrySubsystem>("m_registry");
        // load registries here??
        createSubsystem<InputSubsystem>("input");
        createSubsystem<StateSubsystem>("state");
        // get state subsystem -> setInitialState<MyState>();??
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

    Subsystem* Engine::addSubsystem(const std::string& name, std::unique_ptr<Subsystem> subsystem)
    {
        Debug::print("  Initialising " + name + " subsystem...");
        m_subsystems[name] = std::move(subsystem);
        m_subsystems[name]->outer = this;
        m_subsystems[name]->init(*this);
        Debug::print("  " + name + " subsystem initialised.");
        return m_subsystems[name].get();
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
    }

    void Engine::preTick()
    {
        for (auto& subsystemPair : m_subsystems)
        {
            subsystemPair.second->preTick();

            if (subsystemPair.second->pendingCreate)
            {
                subsystemPair.second->pendingCreate = false;
                //subsystemPair.second->init(*this);
            }
        }
    }

    void Engine::tick(sf::Time& time)
    {
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

        for (auto& subsystemPair : m_subsystems)
        {
            // collate views into one here? window does that be default anyway? hmm?
            if (!subsystemPair.second->pendingCreate)
            {
                m_window->draw(*subsystemPair.second);
            }
        }

        m_window->display();
    }

    void Engine::postTick()
    {
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
        deinitSubsystems();
        Debug::print("Engine deinitialised. Exiting...");
    }
}
