project(Tails)

target_sources(
    Tails
    PRIVATE
        AssetManager.cpp
        AssetRegistry.cpp
        AssetPtr.cpp
        AssetDeleter.cpp
        AssetSubsystem.cpp
        
        Texture.cpp
        Sound.cpp
)

add_subdirectory(Loaders)
