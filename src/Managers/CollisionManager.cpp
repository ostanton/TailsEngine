#include "TailsEngine/Managers/CollisionManager.h"

#include "TailsEngine/Core/Entity.h"

bool tails::CollisionManager::checkCollision(Entity* entity1, Entity* entity2)
{/*
    // Do nothing if either entities are invalid
    if (!isObjectValid(entity1) || !isObjectValid(entity2))
        return false;
    
    // Physical collision is true
    if (entity1->getGlobalBounds().intersects(entity2->getGlobalBounds()))
    {
        if (!entity1->m_colliding)
        {
            entity1->m_colliding = true;
            // Add entity2 to colliding entities vector
            entity1->m_lastCollidingEntity = entity2;
            entity1->m_collidingEntities.emplace_back(entity2);
            entity1->onStartCollision(entity2, entity2->getGlobalBounds());
        }

        // TODO - outer gets lots in translation somehow
        entity1->onCollision(entity1->m_collidingEntities);
        
        return true;
    }

    // Physical collision is false
    
    if (entity1->m_colliding)
    {
        // Remove entity2 from colliding entities vector
        entity1->m_lastCollidingEntity = nullptr;
        entity1->m_colliding = false;
        // TODO - Iterator out of range when colliding with second CollisionTest object?
        //entity1->m_collidingEntities.erase(std::ranges::find(
        //    entity1->m_collidingEntities.begin(), entity1->m_collidingEntities.end(), entity2));
        entity1->onEndCollision(entity2, entity2->getGlobalBounds());
    }
    */
    return false;
}
