#ifndef TESTGAME_MYENTITY_HPP
#define TESTGAME_MYENTITY_HPP

#include <Tails/Entities/RectEntity.hpp>

using namespace tails;

class MyEntity : public RectEntity
{
    enum class MoveDirection
    {
        None,
        Up,
        Down,
        Left,
        Right
    };

public:
    MyEntity();

private:
    void spawn() override;
    void tick(float deltaTime) override;

    void handleStartMoveUp();
    void handleStartMoveDown();
    void handleStartMoveLeft();
    void handleStartMoveRight();
    void handleStopMove();

    float tileSize {32.f};
    float speed {100.f};
    MoveDirection direction {MoveDirection::None};
    float tileOffset {0.f};
};

#endif //TESTGAME_MYENTITY_HPP
