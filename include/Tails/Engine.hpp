#ifndef TAILS_ENGINE_HPP
#define TAILS_ENGINE_HPP

#include <Tails/StateStack.hpp>
#include <Tails/Object.hpp>

#include <string>
#include <unordered_map>

namespace sf
{
    class RenderWindow;
    class Time;
}

namespace tails
{
    class EngineSubsystem;
    class ManagerSubsystem;

    class Engine : public Object
    {
    public:
        Engine();
        ~Engine();

        struct Paths
        {
            std::string data;
            std::string textures;
            std::string sounds;
            std::string fonts;
            std::string levels;
            std::string input;
            std::string saves;

            void printPaths();
        };

        struct WindowSettings
        {
            std::string title;
            sf::Vector2u size {640, 480};
            bool fullscreen {false};

            void printSettings();
            sf::Uint32 getWindowStyle();
        };

        StateStack& getStateStack() {return m_stateStack;}
        const Paths& getFilePaths() {return m_paths;}

        void initialise();
        void run();

        sf::RenderWindow& getWindow();

        template<typename T>
        T* getSubsystem(const std::string& name)
        {
            static_assert(std::is_base_of_v<EngineSubsystem, T>, "Failed to get typed engine subsystem. Template parameter does not derive EngineSubsystem.");
            return static_cast<T*>(getSubsystem(name));
        }

        EngineSubsystem* getSubsystem(const std::string& name);
        ManagerSubsystem& getManagerSubsystem();

    protected:
        virtual void loadIni();

        // subsystems
        virtual void initSubsystems();
        virtual void deinitSubsystems();

        template<typename T>
        void createSubsystem(const std::string& name)
        {
            static_assert(std::is_base_of_v<EngineSubsystem, T>, "Failed to create engine subsystem. It does not derive EngineSubsystem.");
            addSubsystem(name, std::make_unique<T>());
        }

        void addSubsystem(const std::string& name, std::unique_ptr<EngineSubsystem> subsystem);
        void destroySubsystem(const std::string& name);

    private:
        void initWindow();
        void setupStates();

        void preTick() override;
        void tick(sf::Time& time);
        void draw();
        void postTick() override;
        void deinitialise();

        std::unique_ptr<sf::RenderWindow> m_window; // ptr because we want to initialise it after contructor
        float m_lifetime {0.f};

        StateStack m_stateStack;
        std::unordered_map<std::string, std::unique_ptr<EngineSubsystem>> m_subsystems;

        Paths m_paths;
        WindowSettings m_windowSettings;
        sf::Vector2f m_internalRes {640.f, 480.f};
    };
}

#endif // TAILS_ENGINE_HPP
