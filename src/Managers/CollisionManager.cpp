#include "TailsEngine/Managers/CollisionManager.h"

#include <ranges>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "TailsEngine/Core/Entity.h"

bool tails::CollisionManager::checkCollision(Entity* entity1, Entity* entity2)
{
    // Very shoddy and doesn't really work
    bool colliding {false};
    /*
    for (auto& hitBox1 : entity1->m_hitBoxes)
    {
        for (auto& hitBox2 : entity2->m_hitBoxes)
        {
            if (hitBox1.first->getGlobalBounds().intersects(hitBox2.first->getGlobalBounds()))
            {
                colliding = true;

                // Add to colliding entities vector if it doesn't already exist
                if (std::find(
                    entity1->m_collidingEntities.begin(),
                    entity1->m_collidingEntities.end(), entity2) == entity1->m_collidingEntities.end()
                    )
                {
                    entity1->m_collidingEntities.emplace_back(entity2);
                    entity1->m_colliding = true;
                    entity1->onStartCollision(entity2);
                }
                
                entity1->onCollision(entity1->m_collidingEntities);

                continue;
            }

            colliding = false;

            // Remove entity2 if it is in the colliding entities vector of entity1
            if (auto collisionIter = std::find(
                entity1->m_collidingEntities.begin(),
                entity1->m_collidingEntities.end(), entity2);
                collisionIter != entity1->m_collidingEntities.end()
                )
            {
                entity1->m_collidingEntities.erase(collisionIter);
                entity1->m_colliding = false;
                entity1->onEndCollision(entity2);
            }
        }
    }
    */
    return colliding;
}
