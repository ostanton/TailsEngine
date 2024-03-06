#include "TailsEngine/Managers/CollisionManager.h"

#include <ranges>
#include <SFML/Graphics/Sprite.hpp>

#include "TailsEngine/Core/Entity.h"

bool tails::CollisionManager::checkCollision(Entity* entity1, Entity* entity2)
{
    if (!isObjectValid(entity1) || !isObjectValid(entity2))
        return false;

    if (entity1 == entity2)
        return false;

    if (entity1->getGlobalEntityBounds().intersects(entity2->getGlobalEntityBounds()))
    {
        entity1->onCollision(entity1->m_collidingEntities);

        if (!entity1->m_colliding)
        {
            entity1->m_collidingEntities.emplace_back(entity2);
            entity1->m_colliding = true;
            entity1->onStartCollision(entity2, entity2->getGlobalEntityBounds());
        }

        return true;
    }

    if (entity1->m_colliding)
    {
        const auto entity1Iter =
        std::ranges::find(entity1->m_collidingEntities.begin(), entity1->m_collidingEntities.end(), entity2);

        if (entity1Iter != entity1->m_collidingEntities.end())
        {
            entity1->m_collidingEntities.erase(entity1Iter);
        }
        
        entity1->m_colliding = false;
        entity1->onEndCollision(entity2, entity2->getGlobalEntityBounds());
    }
    
    return false;
}
