#include <TestGame/MyState.hpp>
#include <Tails/Layers/LevelLayer.hpp>
#include <TestGame/MyEntity.hpp>

void MyState::init(tails::StateSubsystem& subsystem)
{
    State::init(subsystem);

    auto level = createLayer<tails::LevelLayer>();
    getLayer<tails::LevelLayer>(level)->spawnEntity<MyEntity>();
}
