#ifndef TESTGAME_MYREGISTRYSUBSYSTEM_HPP
#define TESTGAME_MYREGISTRYSUBSYSTEM_HPP

#include <Tails/Subsystems/RegistrySubsystem.hpp>

class MyRegistrySubsystem : public tails::RegistrySubsystem
{
private:
    void init(tails::Engine& engine) override;
};


#endif //TESTGAME_MYREGISTRYSUBSYSTEM_HPP
