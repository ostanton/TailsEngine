#ifndef TAILS_MANAGERSUBSYSTEM_HPP
#define TAILS_MANAGERSUBSYSTEM_HPP

#include <Tails/Subsystems/EngineSubsystem.hpp>

#include <unordered_map>
#include <memory>
#include <string>

namespace tails
{
    class Manager;
    class InputManager;
    class AudioManager;
    class AssetManager;

    class ManagerSubsystem : public EngineSubsystem
    {
    public:
        template<typename T>
        void createManager(const std::string& name)
        {
            static_assert(std::is_base_of_v<Manager, T>, "Failed to create manager, type does not derive Manager");
            addManager(name, std::make_unique<T>());
        }

        void addManager(const std::string& name, std::unique_ptr<Manager> manager);
        void destroyManager(const std::string& name);
        void clearManagers();
        Manager* getManager(const std::string& name);

        template<typename T>
        T* getManager(const std::string& name)
        {
            static_assert(std::is_base_of_v<Manager, T>, "Failed to get typed manager. Template parameter does not derive Manager.");
            return static_cast<T*>(getManager(name));
        }

        // references because we can assure these managers are valid
        InputManager& getInputManager();
        AudioManager& getAudioManager();
        AssetManager& getAssetManager();

    protected:
        void init() override;
        void preTick() override;
        void tick(float deltaTime) override;
        void postTick() override;
        void deinit() override;

        std::unordered_map<std::string, std::unique_ptr<Manager>> m_managers;
    };
}

#endif // TAILS_MANAGERSUBSYSTEM_HPP
