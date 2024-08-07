project(TailsEngine)

add_library(
    TailsEngine
    STATIC
    Object.cpp
    Engine.cpp
    World.cpp
    Level.cpp
    InputManager.cpp
    KeyboardDevice.cpp
    Entity.cpp
    AssetCache.cpp
    TextureAsset.cpp
)
