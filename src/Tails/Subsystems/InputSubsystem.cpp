#include <Tails/Subsystems/InputSubsystem.hpp>
#include <Tails/Engine.hpp>

#include <nlohmann/json.hpp>
#include <fstream>
#include <ranges>

namespace tails
{
    void InputSubsystem::addContext(const std::string& name, InputContext&& context)
    {
        m_contexts.try_emplace(name, std::move(context));
    }

    void InputSubsystem::addContext(const std::string& name, const InputContext& context)
    {
        m_contexts[name] = context;
    }

    InputContext& InputSubsystem::getContext(const std::string& name)
    {
        return m_contexts[name];
    }

    void InputSubsystem::removeContext(const std::string& name)
    {
        m_contexts.erase(name);
    }

    void InputSubsystem::init(Engine& engine)
    {
        for (auto& [contextName, contextFile] : engine.getDefaultFiles().inputContexts)
        {
            // load inputs from json via engine's paths variables
            std::fstream jsonStream {engine.getFilePaths().input + contextFile};
            auto json {nlohmann::json::parse(jsonStream)};
            InputContext context;

            for (auto& [name, value] : json.items())
            {
                InputAction action;

                for (auto& key : value.get<std::vector<std::string>>())
                {
                    // TODO - string to enum!!
                }

                context.addAction(name, action);
            }

            addContext(contextName, context);
        }
    }

    void InputSubsystem::tick(float deltaTime)
    {
        // loop contexts
        for (auto& context : std::ranges::views::values(m_contexts))
        {
            context.tick(deltaTime);
        }
    }
}
