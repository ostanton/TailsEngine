project(TailsEngine)

target_sources(
    TailsEngine
    PRIVATE
    Component.hpp
    SpriteComponent.hpp
    CameraComponent.hpp
    ShapeComponent.hpp
    CircleShapeComponent.hpp
    ConvexShapeComponent.hpp
    AnimatedSpriteComponent.hpp
    TileMapComponent.hpp
    TextComponent.hpp
    ParticleComponent.hpp
    TransformComponent.hpp
)
