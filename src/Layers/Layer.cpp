#include <Tails/Layers/Layer.hpp>
#include <Tails/States/State.hpp>

namespace tails
{
    State& Layer::getState()
    {
        return *getTypedOuter<State>();
    }
}
