#ifndef TESTGAME_MYENTITY_HPP
#define TESTGAME_MYENTITY_HPP

#include <Tails/Entities/RectEntity.hpp>

using namespace tails;

class MyEntity : public RectEntity
{
public:
    MyEntity();

private:
    void spawn() override;

    void handleMoveRight();

    float speed {50.f};
};


#endif //TESTGAME_MYENTITY_HPP
