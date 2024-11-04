project(TailsEngine)

target_sources(
    TailsEngine
    PRIVATE
    Component.cpp
    SpriteComponent.cpp
    CameraComponent.cpp
    ShapeComponent.cpp
    CircleShapeComponent.cpp
    ConvexShapeComponent.cpp
    AnimatedSpriteComponent.cpp
    TileMapComponent.cpp
    TextComponent.cpp
    ParticleComponent.cpp
)
