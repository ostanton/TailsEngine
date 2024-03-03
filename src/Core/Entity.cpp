#include "TailsEngine/Core/Entity.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/Level.h"
#include "TailsEngine/Debug/Debug.h"

void tails::Entity::spawn()
{
    
}

void tails::Entity::setupData()
{
    Object::setupData();

    if (m_componentsMap.empty())
        return;

    for (auto& component : m_componentsMap)
    {
        if (component.second.pendingSetup)
            component.second.pendingSetup = false;
    }
}

void tails::Entity::update(float deltaTime)
{
    
}

void tails::Entity::processInput(sf::Event& e)
{
    
}

void tails::Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_componentsMap.empty())
        return;

    for (auto& component : m_componentsMap)
    {
        // Only draw if we are not pending setup
        if (!component.second.pendingSetup)
        {
            states.transform *= getTransform();
            target.draw(*component.first, states);
        }
    }
}

void tails::Entity::cleanupData()
{
    Object::cleanupData();
    
    if (m_componentsMap.empty())
        return;

    for (auto& component : m_componentsMap)
    {
        if (component.second.pendingCleanup)
            m_componentsMap.erase(component.first);
    }
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

tails::World& tails::Entity::getWorld() const
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

tails::Viewport& tails::Entity::getViewport() const
{
    return getLevel().getViewport();
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

bool tails::Entity::destroyComponent(Drawable* componentToDestroy)
{
    const auto compIter = std::find_if(m_componentsMap.begin(), m_componentsMap.end(),
        [componentToDestroy] (const auto& component)
        {
            return component.first.get() == componentToDestroy;
        });

    m_componentsMap.at(compIter->first).pendingCleanup = true;

    return false;
}
