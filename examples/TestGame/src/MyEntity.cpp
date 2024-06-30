#include <TestGame/MyEntity.hpp>
#include <Tails/EngineStatics.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Subsystems/InputSubsystem.hpp>

MyEntity::MyEntity()
{
    getRect().setFillColor(sf::Color(0, 255, 0));
}

void MyEntity::spawn()
{
    Entity::spawn();

    InputContext playerContext;
    InputAction moveRightAction;

    moveRightAction.addKey(Keys::Space);
    moveRightAction.addFunction(ActionTrigger::Triggered, this, &MyEntity::handleMoveRight);

    playerContext.addAction("move_right", moveRightAction);

    EngineStatics::getEngine(this)->getInputSubsystem().addContext("player", playerContext);
}

void MyEntity::handleMoveRight()
{
    move(speed * EngineStatics::getEngineDeltaTime(this), 0.f);
}
