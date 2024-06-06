#include <Tails/Entity.hpp>
#include <Tails/LevelState.hpp>
#include <Tails/StateStack.hpp>

namespace tails
{
    void Entity::destroy()
    {
        pendingDestroy = true;
        // use LevelState's destroyEntity() if we need more than this!
    }

    LevelState& Entity::getLevelState()
    {
        return *getTypedOuter<LevelState>();
    }

    StateStack& Entity::getStateStack()
    {
        return getLevelState().getStateStack();
    }

    Engine& Entity::getEngine()
    {
        return getStateStack().getEngine();
    }
}
