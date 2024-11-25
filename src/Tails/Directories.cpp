#include <Tails/Directories.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Maths.hpp>

#include <nlohmann/json.hpp>

namespace tails
{
    void CDirectories::addDirectory(const std::string_view id, std::filesystem::path&& path)
    {
        if (containsDirectory(id))
            return;

        get().m_dirs.try_emplace(hash(id), std::move(path));
    }

    bool CDirectories::containsDirectory(const std::string_view id)
    {
        return get().m_dirs.contains(hash(id));
    }

    const std::filesystem::path& CDirectories::getDirectory(const std::string_view id)
    {
        return get().m_dirs[hash(id)];
    }

    CDirectories& CDirectories::get()
    {
        static CDirectories instance;
        return instance;
    }
}
