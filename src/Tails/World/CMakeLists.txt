project(Tails)

target_sources(
    Tails
    PRIVATE
        Level.cpp
        Actor.cpp
        WorldSubsystem.cpp
        ActorRegistry.cpp
        Layer.cpp
        CameraActor.cpp
        Camera.cpp
)

add_subdirectory(Components)
