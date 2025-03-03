#ifndef TAILS_INPUT_MANAGER_HPP
#define TAILS_INPUT_MANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Input/Key.hpp>

#include <vector>
#include <string_view>
#include <unordered_map>
#include <filesystem>

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
        [[nodiscard]] static bool isActionActive(std::string_view action);
        [[nodiscard]] static float getActionScalarValue(std::string_view action);

        static void addActionMapping(std::string_view name, SUserKey key);
        static void addActionMapping(std::string_view name, const std::vector<SUserKey>& keys);

        [[nodiscard]] static bool actionExists(std::string_view action);

        static bool loadFromFile(const std::filesystem::path& filename);
        
    private:
        CInputManager() = default;
        
        static CInputManager& get();

        static void addActionMapping(size_t id, const std::vector<SUserKey>& keys);
        [[nodiscard]] static bool actionExists(size_t id);

        std::unordered_map<size_t, std::vector<SUserKey>> m_actions;
    };
}

#endif // TAILS_INPUT_MANAGER_HPP
