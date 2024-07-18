#include <Tails/Layers/Layer.hpp>
#include <Tails/States/State.hpp>

namespace tails
{
    State& Layer::getState()
    {
        return *getTypedOuter<State>();
    }

    Engine& Layer::getEngine()
    {
        return getState().getEngine();
    }
}
