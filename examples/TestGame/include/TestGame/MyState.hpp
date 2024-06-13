#ifndef TESTGAME_MYSTATE_HPP
#define TESTGAME_MYSTATE_HPP

#include <Tails/States/State.hpp>

class MyState : public tails::State
{
private:
    void init(tails::StateSubsystem& subsystem) override;
};

#endif //TESTGAME_MYSTATE_HPP
