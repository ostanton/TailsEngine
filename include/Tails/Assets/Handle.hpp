#ifndef TAILS_ASSET_HANDLE_HPP
#define TAILS_ASSET_HANDLE_HPP

#include <Tails/Core.hpp>

#include <string>

namespace tails::assets
{
    /**
     * Handle to a specific loaded asset
     *
     * TODO - not sure about it being a path, etc. might refactor later into something "better" :/
     */
    struct TAILS_API SHandle final
    {
        const char* path;
        u8 type;

        [[nodiscard]] bool operator==(const SHandle& other) const noexcept
        {
            return path == other.path
                && type == other.type;
        }

        [[nodiscard]] bool isValid() const noexcept;
    };
}

template<>
struct std::hash<tails::assets::SHandle>
{
    [[nodiscard]] std::size_t operator()(const tails::assets::SHandle& s) const noexcept
    {
        // std::string to warrant the header include, otherwise the specialisation fails to compile!
        return std::hash<std::string>{}(s.path);
    }
};

#endif // TAILS_ASSET_HANDLE_HPP
