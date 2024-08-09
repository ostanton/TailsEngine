#ifndef TAILS_DIRECTORIES_HPP
#define TAILS_DIRECTORIES_HPP

#include <Tails/Config.hpp>

#include <nlohmann/json_fwd.hpp>

#include <string>
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
         * Loads and populates the map with the specified directories in the file at the specified path.
         *
         * This is required before accessing directories via ID. They will not exist if this is not called before
         * (this is done automatically in CEngine's constructor).
         * @param json JSON object containing the directories
         */
        static bool loadDirectories(const nlohmann::json& json);
        
        /**
         * Get the directory from its ID.
         * @param id Identifier for directory
         * @return Directory mapped to specified ID
         */
        static std::string getDirectory(const std::string& id);
        
    private:
        static CDirectories& get();

        /**
         * Directories relative to executable, mapped to IDs.
         * 
         * This is used in things like the asset cache, for it to know where to look for a file.
         */
        std::unordered_map<std::string, std::string> m_dirs;
    };
}

#endif // TAILS_DIRECTORIES_HPP
