#include "TailsEngine/Level/Entity.h"

#include "TailsEngine/Core/Level.h"
#include "TailsEngine/Core/World.h"
#include "TailsEngine/Debug/Debug.h"

void tails::Entity::spawn()
{
    
}

void tails::Entity::update(float deltaTime)
{
    // Could check if we want to collide for optimisation
    for (auto& entity : getLevel().entities)
    {
        if (entity.get() == this)
            continue;

        // The actual collision check
        // TODO - could add collision profile enum or something
        // like CollisionType::None, Overlap, Block, etc. That might be more for physics though!
        // TODO - single frame overlap! Not constant like this is
        if (getGlobalBounds().intersects(entity->getGlobalBounds()))
        {
            if (!m_colliding)
            {
                m_colliding = true;
                m_lastCollidingEntity = entity.get();
                onStartCollision(entity.get(), entity->getGlobalBounds());
            }
        }
        else
        {
            if (entity.get() == m_lastCollidingEntity)
            {
                if (m_colliding)
                {
                    m_colliding = false;
                    onEndCollision();
                }
            }
        }
    }
}

void tails::Entity::processInput(sf::Event& e)
{
    
}

void tails::Entity::despawn()
{
    
}

void tails::Entity::destroy() const
{
    getWorld()->destroyEntity(this);
}

tails::Level& tails::Entity::getLevel() const
{
    return *dynamic_cast<Level*>(outer);
}

tails::World* tails::Entity::getWorld() const
{
    return getLevel().getWorld();
}

tails::AssetCache& tails::Entity::getLevelAssetCache() const
{
    return getLevel().getAssetCache();
}

tails::MusicManager& tails::Entity::getLevelMusicManager() const
{
    return getLevel().getMusicManager();
}

void tails::Entity::onCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    
}

void tails::Entity::onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    Debug::log("Start collision");
}

void tails::Entity::onEndCollision()
{
    Debug::log("End collision");
}
