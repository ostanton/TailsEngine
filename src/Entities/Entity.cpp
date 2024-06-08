#include <Tails/Entities/Entity.hpp>

namespace tails
{
    void Entity::destroy()
    {
        pendingDestroy = true;
        // use LevelState's destroyEntity() if we need more than this!
    }
}
