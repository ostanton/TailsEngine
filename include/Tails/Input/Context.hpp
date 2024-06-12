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
        Key key;
        std::vector<std::unique_ptr<InputModifier>> modifiers;

        // add loading from json, allowing optional properties, etc.
    };

    struct TAILS_API ActionMapping final
    {
        ActionMapping() = default;
        explicit ActionMapping(InputAction action)
            : inputAction(std::move(action)) {}

        InputAction inputAction;
        std::vector<MappingData> mappingData;
    };

    class TAILS_API InputContext final
    {
    public:
        // TODO - rule of five
        explicit InputContext() = default;
        InputContext(const InputContext&) = delete;
        InputContext(InputContext&&) noexcept;
        InputContext& operator=(const InputContext&) = delete;

        void addAction(const std::string& id, InputAction action);
        ActionMapping& getActionMapping(const std::string& id);

        std::unordered_map<std::string, ActionMapping>& getMappings();

    private:
        std::unordered_map<std::string, ActionMapping> m_mappings;
    };
}

#endif // TAILS_INPUTCONTEXT_HPP
