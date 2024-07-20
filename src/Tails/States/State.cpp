#include <Tails/States/State.hpp>
#include <Tails/Layers/Layer.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    State::State() = default;
    State::~State() = default;

    Layer& State::getLayer() const
    {
        return *getTypedOuter<Layer>();
    }
}
