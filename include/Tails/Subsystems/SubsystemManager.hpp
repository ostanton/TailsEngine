#ifndef TAILS_SUBSYSTEMMANAGER_HPP
#define TAILS_SUBSYSTEMMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <string>

namespace tails
{
    // manager for subsystems
    // could inherit Tickable but then may need that to be virtual
    // maybe sf::Drawable too

    // we don't really want this class to depend on anything, as to
    // prevent the diamond problem as much as possible
    template<typename C>
    class SubsystemManager
    {
        static_assert(std::is_base_of_v<Subsystem, C>, "Failed to create subsystem manager. Class template parameter does not derive from Subsystem.");

    public:
        template<typename T>
        T* getSubsystem(const std::string& name)
        {
            static_assert(std::is_base_of_v<C, T>, "Failed to get typed subsystem. Template parameter does not derive specified subsystem type.");
            return static_cast<T*>(getSubsystem(name));
        }

        C* getSubsystem(const std::string& name);

        template<typename T>
        void createSubsystem(const std::string& name)
        {
            static_assert(std::is_base_of_v<C, T>, "Failed to create subsystem. It does not derive specified subsystem type.");
            addSubsystem(name, std::make_unique<T>());
        }

        void addSubsystem(const std::string& name, std::unique_ptr<C> subsystem);
        bool destroySubsystem(const std::string& name);

    protected:
        void preTick();
        void tick(float deltaTime);
        void draw(sf::RenderTarget& target);
        void postTick();

    private:
        std::unordered_map<std::string, std::unique_ptr<C>> m_subsystems;
    };
}

#endif // TAILS_SUBSYSTEMMANAGER_HPP
