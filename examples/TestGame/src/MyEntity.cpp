#include <TestGame/MyEntity.hpp>
#include <Tails/EngineStatics.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Subsystems/InputSubsystem.hpp>
#include <Tails/Debug.hpp>

MyEntity::MyEntity()
{
    getRect().setFillColor(sf::Color(0, 255, 0));
    getRect().setSize(sf::Vector2f(tileSize, tileSize));
}

void MyEntity::spawn()
{
    Entity::spawn();

    InputAction moveUpAction;
    moveUpAction.addKey(Keys::Up);
    moveUpAction.addKey(Keys::W);
    moveUpAction.addFunction(ActionTrigger::Triggered, this, &MyEntity::handleStartMoveUp);
    moveUpAction.addFunction(ActionTrigger::Completed, this, &MyEntity::handleStopMove);

    InputAction moveDownAction;
    moveDownAction.addKey(Keys::Down);
    moveDownAction.addKey(Keys::S);
    moveDownAction.addFunction(ActionTrigger::Triggered, this, &MyEntity::handleStartMoveDown);
    moveDownAction.addFunction(ActionTrigger::Completed, this, &MyEntity::handleStopMove);

    InputAction moveLeftAction;
    moveLeftAction.addKey(Keys::Left);
    moveLeftAction.addKey(Keys::A);
    moveLeftAction.addFunction(ActionTrigger::Triggered, this, &MyEntity::handleStartMoveLeft);
    moveLeftAction.addFunction(ActionTrigger::Completed, this, &MyEntity::handleStopMove);

    InputAction moveRightAction;
    moveRightAction.addKey(Keys::Right);
    moveRightAction.addKey(Keys::D);
    moveRightAction.addFunction(ActionTrigger::Triggered, this, &MyEntity::handleStartMoveRight);
    moveRightAction.addFunction(ActionTrigger::Completed, this, &MyEntity::handleStopMove);

    InputContext playerContext;
    playerContext.addAction("move_up", moveUpAction);
    playerContext.addAction("move_down", moveDownAction);
    playerContext.addAction("move_left", moveLeftAction);
    playerContext.addAction("move_right", moveRightAction);

    EngineStatics::getEngine(this)->getInputSubsystem().addContext("player", playerContext);
}

void MyEntity::tick(float deltaTime)
{
    Entity::tick(deltaTime);

    if (direction != MoveDirection::None)
    {
        if (tileOffset < tileSize)
        {
            float frameSpeed {speed * deltaTime};
            tileOffset += frameSpeed;

            switch (direction)
            {
                case MoveDirection::None:
                    break;
                case MoveDirection::Up:
                    move(0.f, -frameSpeed);
                    break;
                case MoveDirection::Down:
                    move(0.f, frameSpeed);
                    break;
                case MoveDirection::Left:
                    move(-frameSpeed, 0.f);
                    break;
                case MoveDirection::Right:
                    move(frameSpeed, 0.f);
                    break;
            }
        }

        if (tileOffset >= tileSize)
        {
            tileOffset = 0.f;
            direction = MoveDirection::None;
        }
    }
}

void MyEntity::handleStartMoveUp()
{
    if (direction == MoveDirection::None)
        direction = MoveDirection::Up;
}

void MyEntity::handleStartMoveDown()
{
    if (direction == MoveDirection::None)
        direction = MoveDirection::Down;
}

void MyEntity::handleStartMoveLeft()
{
    if (direction == MoveDirection::None)
        direction = MoveDirection::Left;
}

void MyEntity::handleStartMoveRight()
{
    if (direction == MoveDirection::None)
        direction = MoveDirection::Right;
}

void MyEntity::handleStopMove()
{
    //Debug::print("Stopped moving!");
}
