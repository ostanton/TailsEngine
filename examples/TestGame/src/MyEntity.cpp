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

    tails::InputContext playerContext;
    tails::InputAction moveRightAction;
    moveRightAction.addFunction(tails::ActionTrigger::Triggered, this, &MyEntity::handleMoveRight);
    tails::ActionMapping actionMapping(moveRightAction);
    actionMapping.mappingData.emplace_back(tails::Keys::Space);
    playerContext.addActionMapping("move_right", actionMapping);

    tails::EngineStatics::getEngine(this)->getInputSubsystem().addContext("player", playerContext);
}

void MyEntity::handleMoveRight(bool value)
{

}
