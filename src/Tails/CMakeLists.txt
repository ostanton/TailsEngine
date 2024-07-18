project(TailsEngine)

add_library(
    TailsEngine
    STATIC
    Debug.cpp
    EngineStatics.cpp
    Engine.cpp
)

add_subdirectory(Assets)
add_subdirectory(Audio)
add_subdirectory(Entities)
add_subdirectory(Input)
add_subdirectory(Layers)
add_subdirectory(Registries)
add_subdirectory(States)
add_subdirectory(Subsystems)
add_subdirectory(UI)
