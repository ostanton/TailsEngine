project(Tails)

target_sources(
    Tails
    PRIVATE
        Level.hpp
        Actor.hpp
        WorldSubsystem.hpp
        ActorRegistry.hpp
        Layer.hpp
        CameraActor.hpp
        Camera.hpp
)

add_subdirectory(Components)
