project(Tails)

target_sources(
    Tails
    PRIVATE
        AssetRegistry.cpp
        AssetPtr.cpp
        AssetSubsystem.cpp
        
        Texture.cpp
        Sound.cpp
)

add_subdirectory(Loaders)
