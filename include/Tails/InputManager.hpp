#ifndef TAILS_INPUTMANAGER_HPP
#define TAILS_INPUTMANAGER_HPP

#include <Tails/Config.hpp>

#include <vector>
#include <string>
#include <unordered_map>

namespace tails
{
    enum class TAILS_API EInputDevice : int
    {
        Unknown,
        Keyboard,
        Mouse,
        Controller,

        Count
    };

    struct TAILS_API SKey final
    {
        SKey(EInputDevice inDevice, int inCode);

        /**
         * The key type, normally set via EInputDevice, i.e. keyboard, mouse, etc.
         */
        int device {0};

        /**
         * The button itself, i.e. on keyboard: 0 = A, 1 = B, etc.
         * Can be set from sf::Keyboard::Key, sf::Mouse::Button, etc.
         */
        int code {0};

        void setDevice(EInputDevice inDevice);

        [[nodiscard]] bool isPressed();

        static EInputDevice inputDeviceFromString(const std::string& device);
        static std::string stringFromInputDevice(EInputDevice device);
    };

    class TAILS_API CInputManager final
    {
    public:
        static bool isActionPressed(const std::string& action);

        static void addAction(std::string name, SKey key);
        static void addAction(std::string name, const std::vector<SKey>& keys);
        
    private:
        static CInputManager& get();

        std::unordered_map<std::string, std::vector<SKey>> m_actions;
    };
}

#endif // TAILS_INPUTMANAGER_HPP
