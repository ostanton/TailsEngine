#pragma once
#include <string>

namespace tails
{
class AssetCache;
}

namespace tails
{
enum class AssetType
{
    None,
    Texture, // sf::Texture
    Sound, // sf::SoundBuffer
    Font // sf::Font
};

/**
 * \brief This is going unused at the moment, might come in handy later down the line
 */
enum class AssetState
{
    None,
    Unloaded,
    Loaded
};

/**
 * \brief A structure that contains information for a certain asset. To get its data, call the templated method
 * getAssetData() with the type you want the data to be (sf::Texture, sf::SoundBuffer, etc.)
 */
struct AssetInfo
{
    friend AssetCache;
    
    AssetType type;
    AssetState state;
    std::string path;
    // Potentially useful in the future
    // std::vector<AssetInfo*> dependencies;

    AssetInfo(
        const AssetType assetType,
        const AssetState assetState,
        std::string assetPath)
            :
    type(assetType),
    state(assetState),
    path(std::move(assetPath)),
    m_data(nullptr) {}

    AssetInfo(
        void* assetData,
        const AssetType assetType,
        const AssetState assetState,
        std::string assetPath)
            :
    type(assetType),
    state(assetState),
    path(std::move(assetPath)),
    m_data(assetData) {}

    // Deleting void* is undefined. Any way to make this better?
    ~AssetInfo() { delete m_data; }

    template<typename T>
    T& getAssetData()
    {
        m_counter++;
        return *static_cast<T*>(m_data);
    }

    /**
     * \brief Gets the use count of this asset
     * \return How many "things" use this asset
     */
    [[nodiscard]] int getUsageCount() const
    {
        return m_counter;
    }

private:
    // Might want to replace void* with a container class like AssetData or something,
    // because void* might produce undefined behaviour
    void* m_data;

    /**
     * \brief The count of how many "things" are using this asset
     */
    int m_counter {0};
};

}
