#ifndef TAILS_ASSET_PATH_HPP
#define TAILS_ASSET_PATH_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Assets/AssetManager.hpp>

#include <memory>
#include <filesystem>

namespace tails
{
    class IAsset;
    
    struct TAILS_API SAssetPath final
    {
        SAssetPath() = default;
        SAssetPath(const char* inPath)
            : path(inPath)
        {}
        SAssetPath(std::filesystem::path inPath)
            : path(std::move(inPath))
        {}
        SAssetPath(const SAssetPath&) = default;
        SAssetPath(SAssetPath&&) noexcept = default;
        SAssetPath& operator=(const SAssetPath&) = default;
        SAssetPath& operator=(SAssetPath&&) noexcept = default;
        ~SAssetPath() = default;
        
        /**
         * Synchronously loads an asset from the already set path
         * @tparam T Asset type
         * @return Loaded asset
         */
        template<Derives<IAsset> T>
        [[nodiscard]] std::shared_ptr<T> load() const
        {
            if (path.empty())
                return nullptr;
            
            return CAssetManager::get().load<T>(path);
        }
        
        std::filesystem::path path;
    };
}

#endif // TAILS_ASSET_PATH_HPP
