#include "TailsEngine/Core/Entity.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "TailsEngine/Core/Level.h"
#include "TailsEngine/Debug/Debug.h"

void tails::Entity::spawn()
{
    
}

void tails::Entity::setupData()
{
    Object::setupData();

    if (!m_hitBoxes.empty())
    {
        for (auto& hitBox : m_hitBoxes)
        {
            if (hitBox.second.pendingSetup)
                hitBox.second.pendingSetup = false;
        }
    }

    if (m_sprites.empty())
        return;

    for (auto& sprite : m_sprites)
    {
        if (sprite.second.pendingSetup)
            sprite.second.pendingSetup = false;
    }
}

void tails::Entity::update(float deltaTime)
{
    if (m_sprites.empty())
        return;

    for (const auto& sprite : m_sprites)
    {
        // Only update if we aren't pending setup or cleanup
        if (!sprite.second.pendingSetup && !sprite.second.pendingCleanup && sprite.first->isAnimated)
            sprite.first->getAnimationPlayer().update(deltaTime);
    }
}

void tails::Entity::processInput(sf::Event& e)
{
    
}

void tails::Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    
    if (m_drawHitBoxes)
    {
        if (m_hitBoxes.empty())
            return;

        for (auto& hitBox : m_hitBoxes)
        {
            if (!hitBox.second.pendingSetup && !hitBox.second.pendingCleanup)
            {
                target.draw(*hitBox.first, states);
            }
        }
    }
    
    if (m_sprites.empty())
        return;

    for (auto& sprite : m_sprites)
    {
        // Only draw if we are not pending setup or cleanup
        if (!sprite.second.pendingSetup && !sprite.second.pendingCleanup)
        {
            target.draw(*sprite.first, states);
        }
    }
}

void tails::Entity::cleanupData()
{
    Object::cleanupData();
    
    if (m_hitBoxes.empty())
        return;

    for (auto& hitBox : m_hitBoxes)
    {
        if (hitBox.second.pendingCleanup)
            m_hitBoxes.erase(hitBox.first);
    }

    if (m_sprites.empty())
        return;

    for (auto& sprite : m_sprites)
    {
        if (sprite.second.pendingCleanup)
            m_sprites.erase(sprite.first);
    }
}

void tails::Entity::despawn()
{
    
}

void tails::Entity::destroy()
{
    m_pendingDestroy = true;
}

tails::Entity::Entity()
{
    
}

tails::Entity::~Entity()
{
    
}

const sf::Vector2i& tails::Entity::getPixelPosition()
{
    return m_pixelPosition;
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

void tails::Entity::onStartCollision(Entity* otherEntity)
{
    Debug::log("Start collision");
}

void tails::Entity::onEndCollision(Entity* otherEntity)
{
    Debug::log("End collision");
}

const std::vector<tails::Entity*>& tails::Entity::getCollidingEntities() const
{
    return m_collidingEntities;
}

void tails::Entity::setInputMode(InputMode inputMode) const
{
    getLevel().setInputMode(inputMode);
}

sf::RectangleShape* tails::Entity::createHitBox(const sf::Vector2f& size,
    const sf::Vector2f& position, const sf::Color& colour)
{
    auto resultShape {new sf::RectangleShape};
    resultShape->setSize(size);
    resultShape->setPosition(position);
    resultShape->setFillColor(colour);
    ComponentInfo shapeInfo;
    shapeInfo.pendingSetup = true;
    m_hitBoxes.emplace(resultShape, shapeInfo);
    return resultShape;
}

void tails::Entity::destroyHitBox(sf::RectangleShape* hitBox)
{
    const auto mapIter = std::find_if(m_hitBoxes.begin(), m_hitBoxes.end(),
        [&](auto& hitBoxIter)
        {
            return hitBoxIter.first.get() == hitBox;
        });

    m_hitBoxes.at(mapIter->first).pendingCleanup = true;
}

tails::AnimatedSprite* tails::Entity::createSprite()
{
    auto resultSprite {new AnimatedSprite};

    ComponentInfo spriteInfo;
    spriteInfo.pendingSetup = true;
    
    m_sprites.emplace(resultSprite, spriteInfo);
    
    return resultSprite;
}

tails::AnimatedSprite* tails::Entity::createSprite(const sf::Texture& spriteSheet)
{
    auto resultSprite {new AnimatedSprite};
    resultSprite->setTexture(spriteSheet);
    
    ComponentInfo spriteInfo;
    spriteInfo.pendingSetup = true;
    
    m_sprites.emplace(resultSprite, spriteInfo);
    
    return resultSprite;
}

void tails::Entity::destroySprite(const AnimatedSprite* sprite)
{
    const auto mapIter = std::find_if(m_sprites.begin(), m_sprites.end(),
        [&](auto& spriteIter)
        {
            return spriteIter.first.get() == sprite;
        });

    m_sprites.at(mapIter->first).pendingCleanup = true;
}

void tails::Entity::drawHitBoxes(bool inDraw)
{
    m_drawHitBoxes = inDraw;
}

bool tails::Entity::getDrawHitBoxes() const
{
    return m_drawHitBoxes;
}

void tails::Entity::setViewCameraPosition(const sf::Vector2f& position) const
{
    getLevel().setViewCameraPosition(position);
}
