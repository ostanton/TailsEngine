#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "AnimatedSprite.h"
#include "TailsEngine/Core/Obj.h"

namespace sf
{
class Event;
class RectangleShape;
}

namespace tails
{
class InputManager;
class World;
class Level;
class CollisionManager;
class MusicManager;
class AssetCache;
class Viewport;
class Component;
enum class InputMode;
}

namespace tails
{
struct ComponentInfo
{
    bool pendingSetup {false};
    bool pendingCleanup {false};
};

/**
 * \brief Base class for all entities. Every entity is a sprite. You do not need to do sprite things however,
 * or have any appearance at all. This might be changed for a more lax sf::Drawable instead of sf::Sprite,
 * like how the widgets work (if they do actually work that is, they might not). For now it is a sprite
 */
class Entity : public Object, public sf::Drawable, public sf::Transformable
{
    friend World;
    friend Level;
    friend CollisionManager;

public:
    /**
     * \brief Destroys this entity. Deletes its memory, removes it from Level, etc.
     */
    void destroy();

    Entity();
    ~Entity() override;

    const sf::Vector2i& getPixelPosition();

protected:
    /**
     * \brief Called when this entity has been created in the level, but not yet spawned. Its position and general
     * SFML settings should be set, but it will not be in the Level's entities vector
     */
    virtual void create();
    
    /**
     * \brief Called once this entity has completely spawned in a level. All its members should be initialised
     */
    virtual void spawn();

    void setupData() override;
    
    /**
     * \brief Called every frame that this entity is alive
     * \param deltaTime Time since last frame
     */
    virtual void update(float deltaTime);

    /**
     * \brief Called before update(). Generally where inputs should go (not a hard rule). Can access sf::RenderWindow's
     * sf::Event events from e
     * \param e Window event from ApplicationWindow
     */
    virtual void processInput(sf::Event& e);

    /**
     * \brief Called every frame after processInput() and update(). This is where you should components are drawn.
     * We multiply our own transform with the states parameter's to have a world transform. Then each component's
     * own transform is local to it
     * \param target The RenderTarget to draw components to
     * \param states RenderStates dictating how components should be drawn
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void cleanupData() override;
    
    /**
     * \brief Called before destruct() when this entity is being removed from a level. Should probably delete
     * any raw pointers contained in the Entity here
     */
    virtual void despawn();
    
    /**
     * \brief Gets the level this entity is contained within
     * \return Pointer to the level
     */
    Level& getLevel() const;

    /**
     * \brief Gets the world this entity and its level are contained within
     * \return Pointer to the world
     */
    World& getWorld() const;

    AssetCache& getLevelAssetCache() const;
    MusicManager& getLevelMusicManager() const;

    Viewport& getViewport() const;

    /**
     * \brief Called every frame while this entity is colliding with any other amount of entities
     * \param otherEntities The vector of entities this entity is colliding with. This is the same as
     * m_collidingEntities, which can be got with getCollidingEntities()
     */
    virtual void onCollision(std::vector<Entity*>& otherEntities);
    
    /**
     * \brief Called the frame we start colliding with another entity
     * \param otherEntity The entity we have just started colliding with
     */
    virtual void onStartCollision(Entity* otherEntity);
    
    /**
     * \brief Called the frame we stop colliding with another entity
     * \param otherEntity The entity we have just stopped colliding with
     */
    virtual void onEndCollision(Entity* otherEntity);

    bool m_colliding {false};
    Entity* m_lastCollidingEntity {nullptr};

    /**
     * \brief Gets all the entities this entity is currently colliding with
     * \return Vector of entities this entity is colliding with
     */
    const std::vector<Entity*>& getCollidingEntities() const;

    void setInputMode(InputMode inputMode);

    sf::RectangleShape* createHitBox(const sf::Vector2f& size = {32.f, 32.f},
        const sf::Vector2f& position = {0.f, 0.f}, const sf::Color& colour = {sf::Color::Red});
    void destroyHitBox(sf::RectangleShape* hitBox);

    AnimatedSprite* createSprite();
    AnimatedSprite* createSprite(const sf::Texture& spriteSheet);
    void destroySprite(const AnimatedSprite* sprite);

    void drawHitBoxes(bool inDraw);
    bool getDrawHitBoxes() const;

    void setViewCameraPosition(const sf::Vector2f& position) const;

private:
    /**
     * \brief Vector of entities we are currently colliding with
     */
    std::vector<Entity*> m_collidingEntities;

    std::unordered_map<unique_ptr<AnimatedSprite>, ComponentInfo> m_sprites;
    std::unordered_map<unique_ptr<sf::RectangleShape>, ComponentInfo> m_hitBoxes;

    /**
     * \brief Whether this entity is awaiting destruction at the end of this frame
     */
    bool m_pendingDestroy {false};

    bool m_drawHitBoxes {false};

    /**
     * \brief Position of this entity rounded to the nearest pixel (will be used to draw the entity at the
     * rounded position eventually)
     */
    sf::Vector2i m_pixelPosition;
};

}
