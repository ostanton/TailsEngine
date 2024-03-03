#include "TailsEngine/Level/Entity.h"

#include "TailsEngine/Core/Level.h"
#include "TailsEngine/Debug/Debug.h"

void tails::Entity::spawn()
{
    
}

void tails::Entity::update(float deltaTime)
{
    /*
    // Could check if we want to collide for optimisation
    for (auto& entity : getLevel().getSpawnedEntities())
    {
        if (entity == this)
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
                m_lastCollidingEntity = entity;
                onStartCollision(entity, entity->getGlobalBounds());
            }
        }
        else
        {
            if (entity == m_lastCollidingEntity)
            {
                if (m_colliding)
                {
                    m_colliding = false;
                    onEndCollision();
                }
            }
        }
    }*/
}

void tails::Entity::processInput(sf::Event& e)
{
    
}

void tails::Entity::despawn()
{
    
}

void tails::Entity::destroy()
{
    m_pendingDestroy = true;
}

void tails::Entity::create()
{
    
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

void tails::Entity::onCollision(std::vector<Entity*>& otherEntities)
{
    // TODO - outer is lost in translation, read CollisionManager for info
    /*
    if (!otherEntities.empty())
    {
        std::cout << "Colliding with: ";
        
        for (const auto otherEntity : otherEntities)
        {
            if (!isObjectValid(otherEntity))
                continue;
            
            std::cout << getObjectClassName(otherEntity) << ", ";
        }

        std::cout << "\n";
    }*/
}

void tails::Entity::onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    Debug::log("Start collision");
}

void tails::Entity::onEndCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    Debug::log("End collision");
}

const std::vector<tails::Entity*>& tails::Entity::getCollidingEntities() const
{
    return m_collidingEntities;
}
