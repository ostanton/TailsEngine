#ifndef TAILS_INPUTCONTEXT_HPP
#define TAILS_INPUTCONTEXT_HPP

#include <Tails/Input/Action.hpp>
#include <Tails/Input/Modifier.hpp>

#include <unordered_map>
#include <string>
#include <vector>

namespace tails
{
    struct MappingData
    {
        // key - struct with SFML enums or my own enum that links to SFML's?? struct probably. variant or just list of members?
        // modifiers
        // etc
        std::vector<std::unique_ptr<InputModifier>> modifiers;

        // add loading from json, allowing optional properties, etc.
    };

    struct ActionMapping final
    {
        ActionMapping() = default;
        ActionMapping(InputAction action)
            : inputAction(action) {}

        InputAction inputAction;
        std::vector<MappingData> mappingData;
    };

    class InputContext final
    {
    public:
        // TODO - rule of five
        explicit InputContext() = default;
        InputContext(const InputContext&) = delete;
        InputContext& operator=(const InputContext&) = delete;

        void addAction(const std::string& id, InputAction action);
        ActionMapping& getActionMapping(const std::string& id);

    private:
        std::unordered_map<std::string, ActionMapping> m_mappings;
    };
}

#endif // TAILS_INPUTCONTEXT_HPP
