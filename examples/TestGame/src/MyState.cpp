#include <TestGame/MyState.hpp>
#include <Tails/Layers/LevelLayer.hpp>
#include <TestGame/MyEntity.hpp>
#include <TestGame/MyScreen.hpp>

void MyState::init(tails::StateSubsystem& subsystem)
{
    State::init(subsystem);

    auto level = createLayer<tails::LevelLayer>();
    createLayer<MyScreen>();
    getLayer<tails::LevelLayer>(level)->spawnEntity<MyEntity>();
    //getLayer<tails::LevelLayer>(level)->spawnEntity<tails::RectEntity>();
}
