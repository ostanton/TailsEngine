#ifndef TAILS_ENGINE_HPP
#define TAILS_ENGINE_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

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
    class State;

    struct TAILS_API Paths
    {
        std::string data {"res/data/"};
        std::string textures {"res/tex/"};
        std::string sounds {"res/sound/"};
        std::string fonts {"res/font/"};
        std::string levels {"res/level/"};
        std::string input {data + "/input/"};
        std::string saves {"save/"};

        void printPaths() const;
    };

    /**
     * All data to do with how the game renders/draws
     * Maybe shaders will be stored here??
     */
    struct TAILS_API RenderSettings
    {
        sf::Vector2f size {640, 480};

        void printSettings() const;
    };

    /**
     * All window information/settings. This is volatile, but realistically,
     * only the fullscreen and maybe the size should change
     */
    struct TAILS_API WindowSettings
    {
        std::string title {"Tails Engine"};
        sf::Vector2u size {640, 480};
        bool fullscreen {false};
        bool vsync {false};
        unsigned int framerateLimit {0};

        void printSettings() const;
        [[nodiscard]] sf::Uint32 getWindowStyle() const;
    };

    class TAILS_API Engine : public Object, public Tickable
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

        float getDeltaTime() const {return m_deltaTime;}

    protected:
        virtual void loadIni();

        // subsystems
        virtual void initCustomSubsystems();
        void initSubsystems();
        void deinitSubsystems();

        template<typename T>
        T* createSubsystem(const std::string& name)
        {
            static_assert(std::is_base_of_v<Subsystem, T>, "Failed to create engine subsystem. It does not derive Subsystem.");
            return static_cast<T*>(addSubsystem(name, std::make_unique<T>()));
        }

        Subsystem* addSubsystem(const std::string& name, std::unique_ptr<Subsystem> subsystem);
        void destroySubsystem(const std::string& name);

        /* Default but overridable stuff */
        virtual std::unique_ptr<RegistrySubsystem> setupDefaultRegistrySubsystem();
        virtual std::unique_ptr<State> setupDefaultState();

        std::string m_engineIniSource {"engine.ini"};

    private:
        void initWindow();

        void preTick() override;
        void tick(float deltaTime) override;
        void draw();
        void postTick() override;
        /**
         * Called once the main loop has exited. Not called in the destructor
         */
        void deinitialise();

        std::unique_ptr<sf::RenderWindow> m_window; // ptr because we want to initialise it after contructor
        float m_lifetime {0.f}; // how long the engine has been alive/ticking/running, etc.
        float m_deltaTime {0.f}; // length of current frame

        std::unordered_map<std::string, std::unique_ptr<Subsystem>> m_subsystems;

        Paths m_paths;
        RenderSettings m_renderSettings;
        WindowSettings m_windowSettings;
    };
}

#endif // TAILS_ENGINE_HPP
