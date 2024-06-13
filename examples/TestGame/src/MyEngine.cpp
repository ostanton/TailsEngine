#include <TestGame/MyEngine.hpp>
#include <TestGame/MyState.hpp>
#include <TestGame/MyRegistrySubsystem.hpp>

std::unique_ptr<tails::RegistrySubsystem> MyEngine::setupDefaultRegistrySubsystem()
{
    return std::make_unique<MyRegistrySubsystem>();
}

std::unique_ptr<tails::State> MyEngine::setupDefaultState()
{
    return std::make_unique<MyState>();
}
