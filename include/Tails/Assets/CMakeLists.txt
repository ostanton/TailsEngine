project(Tails)

target_sources(
    Tails
    PRIVATE
        Asset.hpp
        AssetManager.hpp
        AssetRegistry.hpp
        AssetType.hpp
        AssetPtr.hpp
        AssetDeleter.hpp
        AssetSubsystem.hpp
        
        Texture.hpp
        Sound.hpp
        Level.hpp
)

add_subdirectory(Loaders)
