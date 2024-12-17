#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Serialisable.hpp>
#include <Tails/ClassRegistry.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <memory>

namespace sf
{
    class Transform;
}

namespace tails
{
    class CLevel;
    class CEngine;
    class CResourceManager;
    class CComponent;
    class CTransformComponent;

    /**
     * A class that can be spawned in a CLevel. Its root component is its transform representation.
     * Instead of an ECS, where an entity is the sum of its components, the entity is instead its own thing,
     * with optional components for additional functionality.
     *
     * If you wanted to, you could use it like an ECS, have a player controller as a component and not subclass
     * the entity. The entity's representation in the world is actually just the sum of its components.
     */
    class TAILS_API CEntity :
        public CObject,
        public ITickable,
        public ISerialisable,
        public sf::Drawable
    {
        friend CLevel;

    public:
        CEntity();
        CEntity(const CEntity&) = delete;
        CEntity(CEntity&&) noexcept = default;
        CEntity& operator=(const CEntity&) = delete;
        CEntity& operator=(CEntity&&) noexcept = default;
        ~CEntity() override;
        
        /**
         * Mark this entity for destruction at the start of the next frame.
         */
        void destroy();

        /**
         * Check if this entity is colliding with another.
         * @param entity The entity we're testing collision with
         */
        bool colliding(const CEntity* entity) const;

        [[nodiscard]] sf::FloatRect getLocalBounds() const;
        [[nodiscard]] sf::FloatRect getGlobalBounds() const;

        /**
         * Gets the level that this entity belongs to
         * @return Owning level
         */
        [[nodiscard]] CLevel& getLevel() const;
        [[nodiscard]] CEngine& getEngine() const;

        /**
         * Sets the position of this entity's root component
         * @param position New position
         */
        void setPosition(const sf::Vector2f& position) const;

        /**
         * Sets the rotation of this entity's root component
         * @param angle New rotation
         */
        void setRotation(const sf::Angle& angle) const;

        /**
         * Sets the scale of this entity's root component
         * @param scale New scale
         */
        void setScale(const sf::Vector2f& scale) const;

        void move(const sf::Vector2f& offset) const;

        /**
         * Gets the position of this entity's root component
         * @return Entity position
         */
        [[nodiscard]] sf::Vector2f getPosition() const;
        
        /**
         * Gets the rotation of this entity's root component
         * @return Entity rotation
         */
        [[nodiscard]] sf::Angle getRotation() const;
        
        /**
         * Gets the scale of this entity's root component
         * @return Entity scale
         */
        [[nodiscard]] sf::Vector2f getScale() const;

        /**
         * Gets the transform of this entity's root component
         * @return Entity transform
         */
        [[nodiscard]] const sf::Transform& getTransform() const;

        /**
         * Gets the inverse transform of this entity's root component
         * @return Entity inverse transform
         */
        [[nodiscard]] const sf::Transform& getInverseTransform() const;

        void setRootComponent(CTransformComponent* component);
        
        [[nodiscard]] CTransformComponent* getRootComponent() const {return m_rootComponent;}

        template<Derives<CComponent> T>
        [[nodiscard]] T* getRootComponent() const {return static_cast<T*>(m_rootComponent);}

        template<Derives<CComponent> T, typename... ArgsT>
        requires ConstructibleUserType<T, ArgsT...>
        T* createComponent(ArgsT&&... args)
        {
            return static_cast<T*>(addComponent(std::unique_ptr<T>(newObject<T>(this, std::forward<ArgsT>(args)...))));
        }

        CComponent* createRegisteredComponent(std::string_view name);

        template<Derives<CComponent> T>
        T* createRegisteredComponent(const std::string_view name)
        {
            return static_cast<T*>(addComponent(std::unique_ptr<T>(newObject<T>(name, this))));
        }
        
    protected:
        /**
         * A place to load all the resources that this entity requires/depends on
         * @param resourceManager The resource manager associated with the level this entity is spawned in
         */
        virtual void loadResources(CResourceManager& resourceManager) {}

        /**
         * Called before spawn(), used to initialise this entity's components
         */
        virtual void initComponents();
        
        /**
         * Called the same frame as this entity is spawned.
         */
        virtual void spawn() {}

        /**
         * Called the start of the next frame after this entity is spawned.
         */
        virtual void postSpawn() {}

        /**
         * Called the same frame this entity is despawned/marked for destroy.
         */
        virtual void despawn() {}

        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        /**
         * Called every frame while we are colliding with another entity.
         * @param other The entity we are colliding against
         */
        virtual void collision(CEntity& other) {}

        [[nodiscard]] CComponent* addComponent(std::unique_ptr<CComponent> component);

    private:
        void serialise(nlohmann::json& obj) const override;
        void deserialise(const nlohmann::json& obj) override;

        std::vector<std::unique_ptr<CComponent>> m_components;
        CTransformComponent* m_rootComponent {nullptr};
    };
}
TAILS_REGISTER_CLASS_CUSTOM_NAME(CEntity, "Entity")

#endif // TAILS_ENTITY_HPP
