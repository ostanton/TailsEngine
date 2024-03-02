#pragma once

namespace tails
{
class Entity;
}

namespace tails
{
class CollisionManager
{
public:
    /**
     * \brief Checks if there is a collision between two entities
     * \param entity1 The entity doing the collision
     * \param entity2 The entity being collided with
     * \return Was there a collision?
     */
    static bool checkCollision(Entity* entity1, Entity* entity2);
};

}
