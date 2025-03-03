project(TailsEngine)

add_library(
    TailsEngine
    STATIC
    Object.cpp
    Engine.cpp
    Level.cpp
    Entity.cpp
    ResourceManager.cpp
    Directories.cpp
    Debug.cpp
    Localisation.cpp
    LocaleString.cpp
    Subsystem.cpp
    LevelSubsystem.cpp
    Instance.cpp
)

add_subdirectory(Assets)
add_subdirectory(Audio)
add_subdirectory(Components)
add_subdirectory(Input)
add_subdirectory(Network)
add_subdirectory(Resources)
add_subdirectory(Types)
add_subdirectory(UI)
