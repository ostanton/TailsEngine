#include <Tails/Directories.hpp>
#include <Tails/Debug.hpp>

#include <nlohmann/json.hpp>

namespace tails
{
    bool CDirectories::loadDirectories(const nlohmann::json& json)
    {
        if (json.is_null())
            // failed to load json file
            return false;

        CDebug::print("Looping directories");
        for (auto& [dirKey, dirValue] : json.items())
        {
            get().m_dirs.try_emplace(dirKey, dirValue.get<std::string>());
        }

        return true;
    }
    
    std::string CDirectories::getDirectory(const std::string& id)
    {
        if (get().m_dirs.contains(id))
            return get().m_dirs[id];

        return {};
    }

    CDirectories& CDirectories::get()
    {
        static CDirectories instance;
        return instance;
    }
}
