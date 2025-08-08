project(Tails)

target_sources(
    Tails
    PRIVATE
        Level.cpp
        Actor.cpp
        WorldSubsystem.cpp
        ActorRegistry.cpp
        CameraActor.cpp
        Camera.cpp
        CollisionManager.cpp
)

add_subdirectory(Components)
