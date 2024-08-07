#ifndef TAILS_INPUTMANAGER_HPP
#define TAILS_INPUTMANAGER_HPP

#include <Tails/Config.hpp>

#include <memory>
#include <vector>
#include <string>

namespace tails
{
    class IInputDevice;

    struct SAction
    {
        std::string name;
        std::vector<int> buttons;

        [[nodiscard]] bool isDeviceButtonPressed(IInputDevice& device) const;

        void addButton(int button);

        bool operator==(const SAction& other) const;
    };
    
    class TAILS_API CInputManager final
    {
    public:
        template<typename T>
        static void registerInputDevice()
        {
            static_assert(std::is_base_of_v<IInputDevice, T>,
                "Failed to register input device, it does not derive IInputDevice.");
            get().m_devices.emplace_back(std::make_unique<T>());
        }
        
        static bool isActionPressed(const SAction& action);
        static bool isActionPressed(const std::string& action);

        static SAction& addAction(const SAction& action);
        static SAction& addAction(std::string name, const std::vector<int>& buttons);
        
    private:
        CInputManager();
        
        static CInputManager& get();

        std::vector<SAction> m_actions;
        std::vector<std::unique_ptr<IInputDevice>> m_devices;
    };
}

#endif // TAILS_INPUTMANAGER_HPP
