#include <Tails/Engine.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Subsystems/AssetSubsystem.hpp>
#include <Tails/Subsystems/AudioSubsystem.hpp>
#include <Tails/Subsystems/RegistrySubsystem.hpp>
#include <Tails/Subsystems/InputSubsystem.hpp>
#include <Tails/Subsystems/StateSubsystem.hpp>
#include <Tails/States/State.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <mini/ini.h>
#include <iostream>

namespace tails
{
    Engine::Engine() = default;
    Engine::~Engine() = default;

    void Paths::printPaths() const
    {
        std::cout
            << "\nPaths:\n"
            << "  Data = " << data << "\n"
            << "  Textures = " << textures << "\n"
            << "  Sounds = " << sounds << "\n"
            << "  Fonts = " << fonts << "\n"
            << "  Levels = " << levels << "\n"
            << "  Input = " << input << "\n"
            << "  Saves = " << saves << "\n";
    }

    void RenderSettings::printSettings() const
    {
        std::cout << "\nRender:\n"
            << "  Resolution = " << size.x << "x" << size.y << "\n";
    }

    void WindowSettings::printSettings() const
    {
        std::cout << "\nWindow:\n"
                  << "  Title = " << title << "\n"
                  << "  Size = " << size.x << "x" << size.y << "\n"
                  << "  Fullscreen = " << fullscreen << "\n"
                  << "  Vertical Sync = " << vsync << "\n"
                  << "  Framerate Limit = " << framerateLimit << "\n";
    }

    sf::Uint32 WindowSettings::getWindowStyle() const
    {
        return fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    }

    void Engine::initialise()
    {
        Debug::print("Initialising engine...");
        loadIni();
        Debug::print("Initialising custom subsystems...\n");
        initCustomSubsystems();
        Debug::print("Custom subsystems initialised!\n");
        initSubsystems();
        Debug::print("Engine subsystems initialised.\n");
        initWindow();
        Debug::print("Window initialised!\n");
        postInitSubsystems();
        m_running = true;
        Debug::print("Engine initialised!\n");
    }

    void Engine::run()
    {
        Debug::print("Begin game loop.\n");
        sf::Clock clock;

        while (m_running)
        {
            preTick();

            sf::Event ev;
            m_deltaTime = clock.restart().asSeconds();

            if (m_window->isOpen())
            {
                while (m_window->pollEvent(ev))
                {
                    switch (ev.type)
                    {
                        default:
                            break;
                        case sf::Event::Closed:
                            // kill the engine, this is the expected behaviour of games and general programs.
                            // you don't want the engine still running in the background with no window!
                            killEngine();
                    }
                }
            }

            tick(m_deltaTime);
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
        return *getSubsystem<RegistrySubsystem>("registry");
    }

    InputSubsystem& Engine::getInputSubsystem()
    {
        return *getSubsystem<InputSubsystem>("input");
    }

    StateSubsystem& Engine::getStateSubsystem()
    {
        return *getSubsystem<StateSubsystem>("state");
    }

    void Engine::killEngine()
    {
        m_running = false;
    }

    void Engine::closeWindow()
    {
        m_window->close();
    }

    void Engine::loadIni()
    {
        Debug::print("Loading engine initialisation file.");
        
        mINI::INIFile engineIniFile(m_engineIniSource); // reference to ini file?
        mINI::INIStructure engineIni; // structure to hold the data itself

        // read file into structure
        if (!engineIniFile.read(engineIni))
        {
            // fails
            Debug::print("Failed to load engine initialisation file");
            Debug::print("Using engine defaults.");
            return;
        }

        auto stringToBool = [](const std::string& string) -> bool
        {
            std::string lowercase {string};
            // transform to lowercase
            std::ranges::transform(lowercase.begin(), lowercase.end(), lowercase.begin(),
                [](const unsigned char c)
                {
                    return std::tolower(c);
                });
            
            if (lowercase == "true" || string == "1")
                return true;

            return false;
        };
        
        if (engineIni.has("paths"))
        {
            auto& pathsSection = engineIni["paths"];
            // add trailing forward-slash
            m_paths.data = pathsSection["data"] + "/";
            m_paths.textures = pathsSection["textures"] + "/";
            m_paths.sounds = pathsSection["sounds"] + "/";
            m_paths.fonts = pathsSection["fonts"] + "/";
            m_paths.levels = pathsSection["levels"] + "/";
            m_paths.input = pathsSection["input"] + "/";
            m_paths.saves = pathsSection["saves"] + "/";

            m_paths.printPaths();
        }
        else
        {
            // fails to find section
            Debug::print("Failed to get paths section");
            Debug::print("Using engine defaults.");
        }

        if (engineIni.has("render"))
        {
            auto& renderSection = engineIni["render"];
            m_renderSettings.size.x = std::stof(renderSection["resolution_x"]);
            m_renderSettings.size.y = std::stof(renderSection["resolution_y"]);

            m_renderSettings.printSettings();
        }
        else
        {
            Debug::print("Failed to get render section");
            Debug::print("Using engine defaults.");
        }

        if (engineIni.has("window"))
        {
            auto& windowSection = engineIni["window"];
            m_windowSettings.title = windowSection["title"];
            m_windowSettings.size.x = std::stoi(windowSection["size_x"]);
            m_windowSettings.size.y = std::stoi(windowSection["size_y"]);
            m_windowSettings.fullscreen = stringToBool(windowSection["fullscreen"]);
            m_windowSettings.vsync = stringToBool(windowSection["vsync"]);
            m_windowSettings.framerateLimit = std::stoi(windowSection["framerate_limit"]);

            m_windowSettings.printSettings();
        }
        else
        {
            Debug::print("Failed to get window section");
            Debug::print("Using engine defaults.");
        }

        if (engineIni.has("contexts"))
        {
            for (auto const& [name, file] : engineIni["contexts"])
            {
                m_defaultFiles.inputContexts[name] = file;
                Debug::print("Loaded " + name + " context, with " + file + " file");
            }
        }
        else
        {
            Debug::print("Failed to get contexts section");
            Debug::print("No input contexts have been loaded.");
        }

        Debug::print("engine.ini loaded!\n");
    }

    void Engine::initSubsystems()
    {
        // subsystems should all be initialised here, and only here.
        // all subsystems must be initialised before the main loop begins
        Debug::print("Initialising engine subsystems:");
        createSubsystem<AssetSubsystem>("asset");
        createSubsystem<AudioSubsystem>("audio");

        // create default registry subsystem, or user's custom one if overridden
        addSubsystem("registry", setupDefaultRegistrySubsystem());

        createSubsystem<InputSubsystem>("input");
        createSubsystem<StateSubsystem>("state")->pushState(setupDefaultState());
        // get state subsystem -> setInitialState<MyState>();??
    }

    void Engine::postInitSubsystems()
    {
        for (auto& [key, subsystem] : m_subsystems)
        {
            subsystem->postInit();
        }
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

        // this isn't really needed, they're smart pointers!
        /*
        Debug::print("Destroying subsystems...");
        m_subsystems.clear();
        Debug::print("Subsystems destroyed.\n");
         */
    }

    Subsystem* Engine::addSubsystem(const std::string& name, std::unique_ptr<Subsystem> subsystem)
    {
        Debug::print("  Initialising " + name + " subsystem...");
        m_subsystems[name] = std::move(subsystem);
        m_subsystems[name]->outer = this;
        m_subsystems[name]->init(*this);
        m_subsystems[name]->pendingCreate = false;
        Debug::print("  " + name + " subsystem initialised.");
        return m_subsystems[name].get();
    }

    std::unique_ptr<RegistrySubsystem> Engine::setupDefaultRegistrySubsystem()
    {
        return std::make_unique<RegistrySubsystem>();
    }

    std::unique_ptr<State> Engine::setupDefaultState()
    {
        return nullptr;
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

        m_window->setVerticalSyncEnabled(m_windowSettings.vsync);
        m_window->setFramerateLimit(m_windowSettings.framerateLimit);
    }

    void Engine::preTick()
    {
        for (auto& subsystemPair : m_subsystems)
        {
            subsystemPair.second->preTick();

            // subsystems should not be added during gameplay
        }
    }

    void Engine::tick(float deltaTime)
    {
        m_lifetime += deltaTime;

        for (auto& subsystemPair : m_subsystems)
        {
            subsystemPair.second->tick(deltaTime);
        }
    }

    void Engine::draw()
    {
        if (!m_window->isOpen()) return;

        m_window->clear();

        // TODO - optimise to only draw subsystems that state they can be drawn??
        for (auto& subsystemPair : m_subsystems)
        {
            // combine sf::Views into one?
            m_window->draw(*subsystemPair.second);
        }

        m_window->display();
    }

    void Engine::postTick()
    {
        for (auto& [key, subsystem] : m_subsystems)
        {
            subsystem->postTick();
        }
    }

    void Engine::deinitialise()
    {
        Debug::print("\nDeinitialising engine...\n");
        Debug::print("Closing the window...");
        m_window->close();
        Debug::print("Window closed!\n");
        deinitSubsystems();
        Debug::print("Engine deinitialised. Exiting...");
    }
}
