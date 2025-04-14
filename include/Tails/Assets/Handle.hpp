#ifndef TAILS_ASSET_HANDLE_HPP
#define TAILS_ASSET_HANDLE_HPP

#include <Tails/Core.hpp>
#include <Tails/String.hpp>

namespace tails::assets
{
    /**
     * Handle to a specific loaded asset
     *
     * TODO - not sure about it being a path, etc. might refactor later into something "better" :/
     */
    struct TAILS_API SHandle final
    {
        SHandle()
            : hash(0), type(0)
        {}
        SHandle(const CString& path, const u8 assetType)
            : hash(std::hash<CString>{}(path)), type(assetType), m_debugPath(path)
        {}

        usize hash;
        u8 type;

        [[nodiscard]] bool operator==(const SHandle& other) const noexcept
        {
            return hash == other.hash
                && type == other.type;
        }

        [[nodiscard]] bool isValid() const noexcept
        {
            return hash != 0; // TODO - make better or something
        }

        [[nodiscard]] const CString& getDebugPath() const noexcept {return m_debugPath;}

    private:
        CString m_debugPath;
    };
}

template<>
struct std::hash<tails::assets::SHandle>
{
    [[nodiscard]] std::size_t operator()(const tails::assets::SHandle& s) const noexcept
    {
        return s.hash;
    }
};

#endif // TAILS_ASSET_HANDLE_HPP
