project(TailsEngine)

target_sources(
    TailsEngine
    PRIVATE
    Assert.hpp
    Config.hpp
    Debug.hpp
    Engine.hpp
    EngineStatics.hpp
    Object.hpp
    Tickable.hpp
    Transform.hpp
)

add_subdirectory(Assets)
add_subdirectory(Audio)
add_subdirectory(Entities)
add_subdirectory(Events)
add_subdirectory(Input)
add_subdirectory(JSON)
add_subdirectory(Layers)
add_subdirectory(Registries)
add_subdirectory(States)
add_subdirectory(Subsystems)
add_subdirectory(UI)
