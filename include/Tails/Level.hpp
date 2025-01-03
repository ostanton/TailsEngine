#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Concepts.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>
#include <vector>
#include <span>
#include <optional>

namespace ldtk
{
    class Level;
}

namespace tails
{
    class CEntity;
    class CEngine;
    class CCameraComponent;
    class CComponent;
    class CLevelSubsystem;

    struct TAILS_API SHitResult final
    {
        CEntity* hitEntity;
        CComponent* hitComponent;
    };
    
    class TAILS_API CLevel final : public CObject, public ITickable, public sf::Drawable, public sf::Transformable
    {
        friend CLevelSubsystem;
        
    public:
        CLevel() = delete;
        explicit CLevel(const ldtk::Level* level);
        CLevel(const CLevel&) = delete;
        CLevel(CLevel&&) noexcept;
        CLevel& operator=(const CLevel&) = delete;
        CLevel& operator=(CLevel&&) noexcept;
        ~CLevel() override;
        
        /**
         * Spawn an entity from its class. The entity in question does not need to be registered in the class registry.
         * @tparam T Entity class
         * @param position Initial position
         * @param rotation Initial rotation
         * @param scale Initial scale
         * @return Pointer to spawned entity
         */
        template<Derives<CEntity> T>
        T* spawnEntity(const sf::Vector2f& position = {0.f, 0.f}, sf::Angle rotation = sf::degrees(0.f), const sf::Vector2f& scale = {1.f, 1.f})
        {
            return static_cast<T*>(spawnEntityImpl(std::unique_ptr<T>(newObject<T>(this)), position, rotation, scale));
        }

        /**
         * Spawns an entity from its class name and casts it to the specified type
         * @tparam T Entity class
         * @param className Registered class name
         * @param position Initial position
         * @param rotation Initial rotation
         * @param scale Initial scale
         * @return Pointer to spawned entity
         */
        template<Derives<CEntity> T>
        T* spawnEntity(std::string_view className, const sf::Vector2f& position = {0.f, 0.f}, sf::Angle rotation = sf::degrees(0.f), const sf::Vector2f& scale = {1.f, 1.f})
        {
            return static_cast<T*>(spawnEntityImpl(std::unique_ptr<T>(newObject<T>(className, this)), position, rotation, scale));
        }

        /**
         * Spawn an entity from its registered class name.
         * @param className Registered class name
         * @param position Initial position
         * @param rotation Initial rotation
         * @param scale Initial scale
         * @return Pointer to spawned entity
         */
        CEntity* spawnEntity(std::string_view className, const sf::Vector2f& position = {0.f, 0.f}, sf::Angle rotation = sf::degrees(0.f), const sf::Vector2f& scale = {1.f, 1.f});

        static void destroyEntity(CEntity* entity);

        [[nodiscard]] CLevelSubsystem& getLevelSubsystem() const;
        [[nodiscard]] CEngine& getEngine() const;

        static bool entitiesColliding(const CEntity* entity1, const CEntity* entity2);

        void setActiveCamera(CCameraComponent* camera);
        void setActiveCameraView(sf::View& view);
        [[nodiscard]] const sf::View& getActiveCameraView() const;
        [[nodiscard]] bool isCameraActive(const CCameraComponent* camera) const;

        [[nodiscard]] std::optional<SHitResult> rectangleTrace(
            sf::FloatRect globalBounds,
            std::span<CEntity*> entitiesToIgnore
        );

        [[nodiscard]] const std::string& getName() const;

        void setParent(CLevel* parent);
        [[nodiscard]] CLevel* getParent() const;
        [[nodiscard]] bool hasSublevel(CLevel* level) const;

    private:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        /**
         * Called when this level is being closed and another is opening.
         */
        void close() const;

        void checkCollision(CEntity* entity) const;

        CEntity* spawnEntityImpl(std::unique_ptr<CEntity> entity, const sf::Vector2f& position, sf::Angle rotation, const sf::Vector2f& scale);
        
        const ldtk::Level* m_level {nullptr};

        std::vector<std::unique_ptr<CEntity>> m_entities;
        std::vector<CLevel*> m_subLevels;

        sf::View m_defaultView;
        sf::View* m_view {&m_defaultView};
    };
}

#endif // TAILS_LEVEL_HPP
