#ifndef TAILS_INPUT_MANAGER_HPP
#define TAILS_INPUT_MANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Key.hpp>

#include <vector>
#include <string>
#include <unordered_map>

namespace tails
{
    class TAILS_API CInputManager final
    {
    public:
        /**
         * Checks whether any key in the given action is either pressed (if button), or active (if scalar).
         * Use this for actions with a mix of buttons and axes
         * @param action The action to check
         * @return If any key bound to the action is "active"
         */
        [[nodiscard]] static bool isActionActive(const std::string& action);
        [[nodiscard]] static float getActionScalarValue(const std::string& action);

        static void addActionMapping(std::string name, SUserKey key);
        static void addActionMapping(std::string name, const std::vector<SUserKey>& keys);

        [[nodiscard]] static bool actionExists(const std::string& action);

        static bool loadFromFile(const std::string& filename);
        
    private:
        static CInputManager& get();

        std::unordered_map<std::string, std::vector<SUserKey>> m_actions;
    };
}

#endif // TAILS_INPUT_MANAGER_HPP
