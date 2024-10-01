#include <Tails/InputManager.hpp>

#include <fstream>
#include <nlohmann/json.hpp>

namespace tails
{
    bool CInputManager::isActionActive(const std::string& action)
    {
        for (auto& [actionName, values] : get().m_actions)
        {
            if (actionName == action)
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

    float CInputManager::getActionScalarValue(const std::string& action)
    {
        if (!actionExists(action)) return 0.f;

        float result {0.f};

        for (auto& axisKey : get().m_actions[action])
        {
            result += axisKey.getScalarAmount();
        }

        return result;
    }

    void CInputManager::addActionMapping(std::string name, SUserKey key)
    {
        addActionMapping(std::move(name), std::vector({key}));
    }

    void CInputManager::addActionMapping(std::string name, const std::vector<SUserKey>& keys)
    {
        if (actionExists(name))
            get().m_actions[name] = keys;
        else
            get().m_actions.try_emplace(std::move(name), keys);
    }

    bool CInputManager::actionExists(const std::string& action)
    {
        return get().m_actions.contains(action);
    }

    bool CInputManager::loadFromFile(const std::string& filename)
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
}
