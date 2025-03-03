#ifndef TAILS_ASSET_HPP
#define TAILS_ASSET_HPP

#include <Tails/Config.hpp>

#include <filesystem>

namespace tails
{
    /**
     * Abstract class for assets loadable from disk
     */
    class TAILS_API IAsset
    {
    public:
        virtual ~IAsset() = default;
        
        [[nodiscard]] virtual bool load(const std::filesystem::path& path) = 0;
    };
}

#endif // TAILS_ASSET_HPP
