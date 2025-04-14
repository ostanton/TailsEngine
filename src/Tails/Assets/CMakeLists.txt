project(Tails)

target_sources(
    Tails
    PRIVATE
        AssetPtr.cpp
        AssetSubsystem.cpp
        
        Texture.cpp
        Sound.cpp
)

add_subdirectory(Loaders)
