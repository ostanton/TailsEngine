#include <Tails/Subsystems/InputSubsystem.hpp>
#include <Tails/Engine.hpp>

#include <nlohmann/json.hpp>
#include <fstream>
#include <ranges>

namespace tails
{
    void InputSubsystem::addContext(const std::string& name, InputContext&& context)
    {
        context.pendingCreate = true;
        m_contexts.try_emplace(name, std::move(context));
    }

    void InputSubsystem::addContext(const std::string& name, const InputContext& context)
    {
        m_contexts[name] = context;
        m_contexts[name].pendingCreate = true;
    }

    InputContext& InputSubsystem::getContext(const std::string& name)
    {
        return m_contexts[name];
    }

    void InputSubsystem::removeContext(const std::string& name)
    {
        if (m_contexts.contains(name))
            m_contexts[name].pendingDestroy = true;
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

    void InputSubsystem::preTick()
    {
        Subsystem::preTick();

        for (auto& context : std::ranges::views::values(m_contexts))
        {
            // contexts don't preTick or postTick (they do but they don't do anything there)
            //context.preTick();

            if (context.pendingCreate)
                context.pendingCreate = false;
        }
    }

    void InputSubsystem::tick(float deltaTime)
    {
        // loop contexts
        for (auto& context : std::ranges::views::values(m_contexts))
        {
            if (!context.pendingCreate)
                context.tick(deltaTime);
        }
    }

    void InputSubsystem::postTick()
    {
        Subsystem::postTick();

        for (auto it = m_contexts.rbegin(); it != m_contexts.rend();)
        {
            //it->second.postTick();

            if (it->second.pendingDestroy)
                m_contexts.erase(it->first);
            else
                ++it;
        }
    }
}
