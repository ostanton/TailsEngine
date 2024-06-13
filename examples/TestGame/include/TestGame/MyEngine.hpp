#ifndef TESTGAME_MYENGINE_HPP
#define TESTGAME_MYENGINE_HPP

#include <Tails/Engine.hpp>

class MyEngine : public tails::Engine
{
private:
    std::unique_ptr<tails::RegistrySubsystem> setupDefaultRegistrySubsystem() override;
    std::unique_ptr<tails::State> setupDefaultState() override;
};

#endif //TESTGAME_MYENGINE_HPP
