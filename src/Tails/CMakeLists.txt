project(TailsEngine)

add_library(
    TailsEngine
    STATIC
    Object.cpp
    Engine.cpp
    World.cpp
    Level.cpp
    LevelSettings.cpp
    InputManager.cpp
    Entity.cpp
    ResourceManager.cpp
    Directories.cpp
    Debug.cpp
    EngineSettings.cpp
    Localisation.cpp
    LocaleString.cpp
    Exception.cpp
    Key.cpp
)

add_subdirectory(Audio)
add_subdirectory(Components)
add_subdirectory(Network)
add_subdirectory(UI)
