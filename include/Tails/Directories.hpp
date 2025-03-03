#ifndef TAILS_DIRECTORIES_HPP
#define TAILS_DIRECTORIES_HPP

#include <Tails/Config.hpp>

#include <string_view>
#include <filesystem>

namespace tails::dir
{
    /**
     * Adds the specified directory. Does nothing if that ID already exists
     * @param id Identifier for directory
     * @param path Directory mapped to specified ID
     */
    TAILS_API void addDirectory(std::string_view id, const std::filesystem::path& path);

    /**
     * Checks whether a directory with the specified ID exists
     * @param id Identifier for directory
     * @return Valid ID
     */
    [[nodiscard]] TAILS_API bool containsDirectory(std::string_view id);

    /**
     * Get the directory from its ID.
     * @param id Identifier for directory
     * @return Directory mapped to specified ID
     */
    [[nodiscard]] TAILS_API const std::filesystem::path& getDirectory(std::string_view id);
}

#endif // TAILS_DIRECTORIES_HPP
