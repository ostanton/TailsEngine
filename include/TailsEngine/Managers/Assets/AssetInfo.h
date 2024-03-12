#pragma once
#include <string>

namespace tails
{
class AssetCache;
}

namespace tails
{
/**
 * \brief A structure that contains information for a certain asset. To get its data, call the templated method
 * getAssetData() with the type you want the data to be (sf::Texture, sf::SoundBuffer, etc.)
 */
struct AssetInfo
{
    friend AssetCache;

    /**
     * \brief The type of the asset. Used because we are storing the data as void*, so without this we would have
     * no idea what type the data is unless we cast and check, which would be a bit annoying. Not to mention
     * static_cast does not care about that stuff really so...
     */
    enum AssetType
    {
        None,     // Invalid/void
        Texture,  // sf::Texture
        Sound,    // sf::SoundBuffer
        Font,     // sf::Font
        Level,    // JSON (.ldtk)
        Screen    // JSON (.screen)
    };

    /**
     * \brief This is going unused at the moment, might come in handy later down the line
     */
    enum AssetState
    {
        Invalid,
        Unloaded,
        Loaded
    };
    
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

    /**
     * \brief Deleting void* is undefined. Any way to make this better? Doesn't matter much as m_data should always be
     * pointing to a valid type no?
     */
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
    /**
     * \brief Might want to replace void* with a container class like AssetData or something,
     * because void* might produce undefined behaviour. It should be fine however, as m_data should always
     * point to a valid type/value
     */
    void* m_data;

    /**
     * \brief The count of how many "things" are using this asset
     */
    int m_counter {0};
};

}
