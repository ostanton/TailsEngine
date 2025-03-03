#include <Tails/Directories.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Maths.hpp>

#include <unordered_map>

namespace tails::dir
{
    std::unordered_map<std::size_t, std::filesystem::path> gDirectories;
    
    void addDirectory(const std::string_view id, const std::filesystem::path& path)
    {
        if (containsDirectory(id))
            return;

        gDirectories.try_emplace(hash(id), std::move(path));
    }

    bool containsDirectory(const std::string_view id)
    {
        return gDirectories.contains(hash(id));
    }

    const std::filesystem::path& getDirectory(const std::string_view id)
    {
        return gDirectories[hash(id)];
    }
}
