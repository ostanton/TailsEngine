#ifndef TESTGAME_MYENTITY_HPP
#define TESTGAME_MYENTITY_HPP

#include <Tails/Entities/RectEntity.hpp>
#include <Tails/Input/Value.hpp>

class MyEntity : public tails::RectEntity
{
public:
    MyEntity();

private:
    void spawn() override;

    void handleMoveRight(bool value);
};


#endif //TESTGAME_MYENTITY_HPP
