#ifndef TAILS_INPUTCONTEXT_HPP
#define TAILS_INPUTCONTEXT_HPP

#include <Tails/Config.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Input/Action.hpp>

#include <unordered_map>
#include <string>
#include <vector>

namespace tails
{
    class InputSubsystem;

    class TAILS_API InputContext final : public Tickable
    {
        friend InputSubsystem;

    public:
        void addAction(const std::string& name, const InputAction& action);
        InputAction& getAction(const std::string& name);
        void removeAction(const std::string& name);

    private:
        void tick(float deltaTime) override;

        std::unordered_map<std::string, InputAction> m_mappings;
    };
}

#endif // TAILS_INPUTCONTEXT_HPP
