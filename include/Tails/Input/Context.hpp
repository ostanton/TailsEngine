#ifndef TAILS_INPUTCONTEXT_HPP
#define TAILS_INPUTCONTEXT_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Input/Action.hpp>

#include <unordered_map>
#include <string>
#include <vector>

namespace tails
{
    class InputSubsystem;

    class TAILS_API InputContext final : public Object, public Tickable
    {
        friend InputSubsystem;

    public:
        InputContext();
        explicit InputContext(const std::unordered_map<std::string, InputAction>& mappings);
        explicit InputContext(const std::pair<std::string, InputAction>& mapping);
        InputContext(const std::string& name, const InputAction& action);
        InputContext(const std::string& name, InputAction&& action);
        InputContext(const InputContext& other);
        InputContext(InputContext&& other) noexcept;
        InputContext& operator=(const InputContext& other);
        InputContext& operator=(InputContext&& other) noexcept;
        ~InputContext() override;
        
        void addAction(const std::string& name, const InputAction& action);
        void addAction(const std::string& name, InputAction&& action);
        [[nodiscard]] InputAction& getAction(const std::string& name);
        void removeAction(const std::string& name);

    private:
        void tick(float deltaTime) override;

        std::unordered_map<std::string, InputAction> m_mappings;
    };
}

#endif // TAILS_INPUTCONTEXT_HPP
