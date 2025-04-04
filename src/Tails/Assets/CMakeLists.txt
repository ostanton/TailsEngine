project(Tails)

target_sources(
    Tails
    PRIVATE
        AssetManager.cpp
        AssetRegistry.cpp
        AssetPtr.cpp
        
        Texture.cpp
        Sound.cpp
)

add_subdirectory(Loaders)
