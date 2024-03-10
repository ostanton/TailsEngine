#include "TailsEngine/Core/Entity.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "TailsEngine/Core/Level.h"
#include "TailsEngine/Core/Components/PrimitiveComponent.h"
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
    if (m_componentsMap.empty())
        return;
    
    for (const auto& component : m_componentsMap)
    {
        if (!component.second.pendingSetup)
            component.first->update(deltaTime);
    }
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
            if (const auto drawable = dynamic_cast<Drawable*>(component.first.get()))
            {
                states.transform *= getTransform();
                target.draw(*drawable, states);
            }
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
    if (m_componentsMap.empty())
        return;
    
    for (auto& component : m_componentsMap)
    {
        component.first->destroy();
    }
}

void tails::Entity::destroy()
{
    m_pendingDestroy = true;
}

void tails::Entity::create()
{
    if (m_componentsMap.empty())
        return;
    
    for (auto& component : m_componentsMap)
    {
        component.first->create();
    }
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

bool tails::Entity::destroyComponent(Component* componentToDestroy)
{
    const auto compIter = std::find_if(m_componentsMap.begin(), m_componentsMap.end(),
        [componentToDestroy] (const auto& component)
        {
            return component.first.get() == componentToDestroy;
        });

    m_componentsMap.at(compIter->first).pendingCleanup = true;

    return false;
}

sf::FloatRect tails::Entity::getGlobalEntityBounds()
{
    sf::FloatRect resultRect;
    for (auto& component : m_componentsMap)
    {
        if (const auto comp = dynamic_cast<PrimitiveComponent*>(component.first.get()))
            resultRect = getTransform().transformRect(comp->getGlobalBounds());
    }

    return resultRect;
}

void tails::Entity::setInputMode(InputMode inputMode)
{
    getLevel().setInputMode(inputMode);
}
