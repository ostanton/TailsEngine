project(TailsEngine)

add_library(
    TailsEngine
    STATIC
    Object.cpp
    Engine.cpp
    Level.cpp
    InputManager.cpp
    Entity.cpp
    ResourceManager.cpp
    Directories.cpp
    Debug.cpp
    Localisation.cpp
    LocaleString.cpp
    Key.cpp
    Subsystem.cpp
    LevelSubsystem.cpp
    Asset.cpp
)

add_subdirectory(Audio)
add_subdirectory(Components)
add_subdirectory(Network)
add_subdirectory(Resources)
add_subdirectory(UI)
