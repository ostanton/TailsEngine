#include <Tails/Assets/AssetDeleter.hpp>
#include <Tails/Assets/AssetManager.hpp>
#include <Tails/Assets/Asset.hpp>

#include <iostream>

namespace tails
{
    void SAssetDeleter::operator()(const IAsset* asset) const noexcept
    {
        std::cout << "Deleting asset with " << assetManagers.size() << " managers\n";
        for (const auto manager : assetManagers)
        {
            std::cout << "Manager has " << manager->m_loadedAssets.size() << " assets\n";
            for (usize i {0}; i < manager->m_loadedAssets.size(); i++)
            {
                //if (manager->m_loadedAssets[i].expired())
                //{
                //    std::cout << "Deleting expired asset!\n";
                //    // TODO - remove expired assets just in case
                //    continue;
                //}

                if (manager->m_loadedAssets[i].lock().get() == asset)
                {
                    std::cout << "Deleted asset!\n";
                    manager->m_loadedAssets.erase(manager->m_loadedAssets.begin() + static_cast<long long>(i));
                    break;
                }
            }
        }
        delete asset;
    }
}
