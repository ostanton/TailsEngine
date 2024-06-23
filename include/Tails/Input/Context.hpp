#ifndef TAILS_INPUTCONTEXT_HPP
#define TAILS_INPUTCONTEXT_HPP

#include <Tails/Config.hpp>
#include <Tails/Input/Action.hpp>
#include <Tails/Input/Modifier.hpp>
#include <Tails/Input/Keys.hpp>

#include <unordered_map>
#include <string>
#include <vector>

namespace tails
{
    // structure that "maps" a Key with other data like a vector of modifiers
    struct TAILS_API MappingData
    {
        explicit MappingData(Key inKey)
            : key(std::move(inKey)) {}

        Key key;
        std::vector<std::unique_ptr<InputModifier>> modifiers;

        // add loading from json, allowing optional properties, etc.
        [[nodiscard]] InputValue getModifiedValue(float deltaTime) const;
    };

    /**
     * Class that acts like a map key-value pair, containing an InputAction and a vector of data mapped to it
     */
    struct TAILS_API ActionMapping final
    {
        ActionMapping() = default;
        explicit ActionMapping(InputAction action)
            : inputAction(std::move(action)) {}

        InputAction inputAction;
        std::vector<MappingData> mappingData;

        [[nodiscard]] bool actionActive();
    };

    class TAILS_API InputContext final
    {
    public:
        explicit InputContext() = default;
        InputContext(const InputContext&) = delete;
        InputContext(InputContext&&) noexcept;
        InputContext& operator=(const InputContext&) = delete;
        InputContext& operator=(InputContext&&) noexcept;

        void addAction(const std::string& id, InputAction action);
        void addActionMapping(const std::string& id, ActionMapping& mapping);
        [[nodiscard]] ActionMapping& getActionMapping(const std::string& id);

        [[nodiscard]] std::unordered_map<std::string, ActionMapping>& getMappings();

    private:
        std::unordered_map<std::string, ActionMapping> m_mappings;
    };
}

#endif // TAILS_INPUTCONTEXT_HPP
