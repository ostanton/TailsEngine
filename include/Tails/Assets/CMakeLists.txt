project(Tails)

target_sources(
    Tails
    PRIVATE
        Asset.hpp
        AssetRegistry.hpp
        AssetType.hpp
        AssetPtr.hpp
        AssetSubsystem.hpp
        
        Texture.hpp
        Sound.hpp
        Level.hpp
)

add_subdirectory(Loaders)
