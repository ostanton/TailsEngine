project(Tails)

target_sources(
    Tails
    PRIVATE
        Asset.hpp
        AssetManager.hpp
        AssetRegistry.hpp
        AssetType.hpp
        AssetPtr.hpp
        
        Texture.hpp
        Sound.hpp
)

add_subdirectory(Loaders)
