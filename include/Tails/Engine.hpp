#ifndef TAILS_ENGINE_HPP
#define TAILS_ENGINE_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>
#include <unordered_map>

namespace sf
{
    class RenderWindow;
    class Time;
}

namespace tails
{
    class Subsystem;
    class AssetSubsystem;
    class AudioSubsystem;
    class RegistrySubsystem;
    class InputSubsystem;
    class StateSubsystem;

    struct TAILS_API Paths
    {
        std::string data;
        std::string textures;
        std::string sounds;
        std::string fonts;
        std::string levels;
        std::string input;
        std::string saves;

        void printPaths() const;
    };

    struct TAILS_API RenderSettings
    {
        sf::Vector2f size {640, 480};

        void printSettings() const;
    };

    struct TAILS_API WindowSettings
    {
        std::string title;
        sf::Vector2u size {640, 480};
        bool fullscreen {false};

        void printSettings() const;
        [[nodiscard]] sf::Uint32 getWindowStyle() const;
    };

    struct TAILS_API EngineSettings
    {
        // initial state to load
        // everything else can be handled from there?
        // registries to use?
    };

    class TAILS_API Engine : public Object
    {
    public:
        Engine();
        ~Engine() override;

        const Paths& getFilePaths() {return m_paths;}
        const RenderSettings& getRenderSettings() {return m_renderSettings;}
        const WindowSettings& getWindowSettings() {return m_windowSettings;}

        void initialise();
        void run();

        sf::RenderWindow& getWindow();

        template<typename T>
        T* getSubsystem(const std::string& name)
        {
            static_assert(std::is_base_of_v<Subsystem, T>, "Failed to get typed engine subsystem. Template parameter does not derive Subsystem.");
            return static_cast<T*>(getSubsystem(name));
        }

        Subsystem* getSubsystem(const std::string& name);
        AssetSubsystem& getAssetSubsystem();
        AudioSubsystem& getAudioSubsystem();
        RegistrySubsystem& getRegistrySubsystem();
        InputSubsystem& getInputSubsystem();
        StateSubsystem& getStateSubsystem();

    protected:
        virtual void loadIni();

        // subsystems
        virtual void initSubsystems();
        virtual void deinitSubsystems();

        template<typename T>
        T* createSubsystem(const std::string& name)
        {
            static_assert(std::is_base_of_v<Subsystem, T>, "Failed to create engine subsystem. It does not derive Subsystem.");
            return static_cast<T*>(addSubsystem(name, std::make_unique<T>()));
        }

        Subsystem* addSubsystem(const std::string& name, std::unique_ptr<Subsystem> subsystem);
        void destroySubsystem(const std::string& name);

    private:
        void initWindow();

        void preTick();
        void tick(sf::Time& time);
        void draw();
        void postTick();
        void deinitialise();

        std::unique_ptr<sf::RenderWindow> m_window; // ptr because we want to initialise it after contructor
        float m_lifetime {0.f}; // how long the engine has been alive/ticking/running, etc.

        std::unordered_map<std::string, std::unique_ptr<Subsystem>> m_subsystems;

        Paths m_paths;
        RenderSettings m_renderSettings;
        WindowSettings m_windowSettings;
    };
}

#endif // TAILS_ENGINE_HPP
