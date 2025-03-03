#ifndef TAILS_ASSET_MANAGER_HPP
#define TAILS_ASSET_MANAGER_HPP

#include <Tails/Config.hpp>

#include <vector>
#include <memory>
#include <filesystem>
#include <functional>

namespace tails
{
    class IAsset;
    
    class TAILS_API CAssetManager final
    {
    public:
        template<typename T>
        [[nodiscard]] std::shared_ptr<T> load(const std::filesystem::path& path)
        {
            auto deleter = [this](T* asset)
            {
                if (const auto it = std::ranges::find_if(m_assets.begin(), m_assets.end(),
                    [asset](const std::shared_ptr<T>& shared)
                    {
                        return shared.get() == asset;
                    });
                    it != m_assets.end()
                )
                {
                    m_assets.erase(it);
                }
            };

            T* const rawAsset {new T};
            m_assets.emplace_back(std::make_shared<T>(rawAsset, std::bind(deleter, rawAsset)));
            const std::shared_ptr<T> result = std::static_pointer_cast<T>(m_assets.back().lock());

            if (!result->load(path))
                return nullptr;

            return result;
        }
        
    private:
        std::vector<std::weak_ptr<IAsset>> m_assets;
    };

    extern CAssetManager gAssetManager;
}

#endif // TAILS_ASSET_MANAGER_HPP
