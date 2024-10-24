#include <Tails/InputManager.hpp>
#include <Tails/Maths.hpp>

#include <fstream>
#include <nlohmann/json.hpp>

namespace tails
{
    bool CInputManager::isActionActive(std::string_view action)
    {
        for (const auto& [actionName, values] : get().m_actions)
        {
            if (actionName == hash(action))
            {
                for (auto& key : values)
                {
                    if (key.isActive())
                        return true;
                }
            }
        }

        return false;
    }

    float CInputManager::getActionScalarValue(std::string_view action)
    {
        if (!actionExists(action)) return 0.f;

        float result {0.f};

        for (auto& axisKey : get().m_actions[hash(action)])
        {
            result += axisKey.getScalarAmount();
        }

        return result;
    }

    void CInputManager::addActionMapping(std::string_view name, SUserKey key)
    {
        addActionMapping(hash(name), std::vector({key}));
    }

    void CInputManager::addActionMapping(std::string_view name, const std::vector<SUserKey>& keys)
    {
        addActionMapping(hash(name), keys);
    }

    bool CInputManager::actionExists(std::string_view action)
    {
        return actionExists(hash(action));
    }

    bool CInputManager::loadFromFile(const std::filesystem::path& filename)
    {
        std::ifstream file {filename};

        if (!file.is_open()) return false;
        
        nlohmann::json inputObj = nlohmann::json::parse(file);

        if (inputObj.is_null()) return false;

        for (auto& [actionName, mappingArr] : inputObj.items())
        {
            std::vector<SUserKey> keys;
            
            for (auto& mappingObj : mappingArr)
            {
                keys.emplace_back(
                    SKey::getKeyFromString(mappingObj["key"].get<std::string>()),
                    mappingObj["scale_multiplier"].get<float>(),
                    mappingObj["dead_zone"].get<float>());
            }
            
            addActionMapping(actionName, keys);
        }

        return true;
    }

    CInputManager& CInputManager::get()
    {
        static CInputManager instance;
        return instance;
    }

    void CInputManager::addActionMapping(size_t id, const std::vector<SUserKey>& keys)
    {
        if (actionExists(id))
            get().m_actions[id] = keys;
        else
            get().m_actions.try_emplace(id, keys);
    }

    bool CInputManager::actionExists(size_t id)
    {
        return get().m_actions.contains(id);
    }
}
