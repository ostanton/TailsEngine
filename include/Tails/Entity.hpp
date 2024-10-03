#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Serialisable.hpp>
#include <Tails/ClassRegistry.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class CLevel;
    class CEngine;
    class CResourceManager;
    class CComponent;
    
    class TAILS_API CEntity :
        public CObject,
        public ITickable,
        public ISerialisable,
        public sf::Drawable,
        public sf::Transformable
    {
        friend CLevel;

    public:
        CEntity();
        CEntity(const CEntity&) = delete;
        CEntity(CEntity&&) = default;
        CEntity& operator=(const CEntity&) = delete;
        CEntity& operator=(CEntity&&) = default;
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

        sf::FloatRect getGlobalBounds() const;

        /**
         * Gets the level that this entity belongs to
         * @return Owning level
         */
        [[nodiscard]] CLevel& getLevel() const;
        [[nodiscard]] CEngine& getEngine() const;

        /**
         * Creates a component regardless of if it is registered
         * @tparam T Component type
         * @tparam ArgsT Constructor argument types
         * @param args Component constructor arguments
         * @return Created component
         */
        template<DerivesComponent T, typename... ArgsT>
        requires ConstructibleUserType<T, ArgsT...>
        T* createComponent(ArgsT&&... args)
        {
            return static_cast<T*>(setupComponent(std::unique_ptr<T>(newObject<T>(this, std::forward<ArgsT>(args)...))));
        }

        /**
         * Creates a component that is registered in the class registry, and casts it to the desired type
         * @tparam T Component type
         * @param className Component registered class name
         * @return Created component
         */
        template<DerivesComponent T>
        T* createRegisteredComponent(std::string_view className)
        {
            return static_cast<T*>(setupComponent(std::unique_ptr<T>(newObject<T>(className, this))));
        }

        /**
         * Creates a component that is registered in the class registry
         * @tparam ArgsT Constructor argument types
         * @param className Component registered class name
         * @return Created component
         */
        CComponent* createRegisteredComponent(std::string_view className);

        template<DerivesComponent T>
        T* getComponent()
        {
            for (auto& comp : m_components)
            {
                if (auto castedComp = dynamic_cast<T*>(comp.get()))
                    return castedComp;
            }

            return nullptr;
        }

        void destroyComponent(CComponent* component);
        
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

        CComponent* setupComponent(std::unique_ptr<CComponent> comp);

    private:
        void serialise(nlohmann::json& obj) const override;
        void deserialise(const nlohmann::json& obj) override;

        std::vector<std::unique_ptr<CComponent>> m_components;
    };
}
TAILS_REGISTER_CLASS(CEntity)

#endif // TAILS_ENTITY_HPP
