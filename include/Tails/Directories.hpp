#ifndef TAILS_DIRECTORIES_HPP
#define TAILS_DIRECTORIES_HPP

#include <Tails/Config.hpp>

#include <filesystem>
#include <string_view>
#include <unordered_map>

namespace tails
{
    /**
     * Singleton that holds all relevant directories mapped to identifiers, like:
     * - texture : res/textures/
     * - etc.
     */
    class TAILS_API CDirectories final
    {
    public:
        /**
         * Adds the specified directory. Does nothing if that ID already exists
         * @param id Identifier for directory
         * @param path Directory mapped to specified ID
         */
        static void addDirectory(std::string_view id, std::filesystem::path&& path);

        /**
         * Checks whether a directory with the specified ID exists
         * @param id Identifier for directory
         * @return Valid ID
         */
        [[nodiscard]] static bool containsDirectory(std::string_view id);
        
        /**
         * Get the directory from its ID.
         * @param id Identifier for directory
         * @return Directory mapped to specified ID
         */
        [[nodiscard]] static const std::filesystem::path& getDirectory(std::string_view id);
        
    private:
        static CDirectories& get();

        /**
         * Directories relative to executable, mapped to IDs.
         * 
         * This is used in things like the asset cache, for it to know where to look for a file.
         */
        std::unordered_map<std::size_t, std::filesystem::path> m_dirs;
    };
}

#endif // TAILS_DIRECTORIES_HPP
