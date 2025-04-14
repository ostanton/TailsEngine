project(Tails)

target_sources(
    Tails
    PRIVATE
        Asset.hpp
        AssetType.hpp
        AssetPtr.hpp
        AssetSubsystem.hpp
        AssetDeleter.hpp
        Handle.hpp
        
        Texture.hpp
        Sound.hpp
        Level.hpp
)

add_subdirectory(Loaders)
