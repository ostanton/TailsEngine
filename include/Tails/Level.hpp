#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/ResourceManager.hpp>
#include <Tails/Concepts.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>

#include <string>
#include <memory>
#include <vector>

namespace tails
{
    class CWorld;
    class CEntity;
    class CEngine;
    struct SLevelSettings;
    class CCameraComponent;
    
    class TAILS_API CLevel final : public CObject, public ITickable, public sf::Drawable
    {
        friend CWorld;
        
    public:
        CLevel() = delete;
        CLevel(const CLevel&) = delete;
        CLevel(CLevel&&) noexcept = default;
        CLevel& operator=(const CLevel&) = delete;
        CLevel& operator=(CLevel&&) noexcept = default;
        ~CLevel() override;
        
        /**
         * Spawn an entity from its class. The entity in question does not need to be registered in the class registry.
         * @tparam T Entity class
         * @param position Initial position
         * @param rotation Initial rotation
         * @param scale Initial scale
         * @return Pointer to spawned entity
         */
        template<DerivesEntity T>
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
        template<DerivesEntity T>
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

        /**
         * Gets the world that this level belongs to
         * @return Owning world
         */
        [[nodiscard]] CWorld& getWorld() const;
        [[nodiscard]] CEngine& getEngine() const;

        static bool entitiesColliding(const CEntity* entity1, const CEntity* entity2);

        void setActiveCamera(CCameraComponent* camera);
        void setActiveCameraView(sf::View& view);
        [[nodiscard]] const sf::View& getActiveCameraView() const;
        [[nodiscard]] bool isCameraActive(const CCameraComponent* camera) const;

        [[nodiscard]] const std::string& getPath() const {return m_path;}
        [[nodiscard]] SLevelSettings& getSettings() const {return *m_settings;}

        CResourceManager resourceManager;
        
    private:
        CLevel(std::string path);

        void open();
        void setSettings(std::unique_ptr<SLevelSettings> settings);

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
        
        std::string m_path;

        /**
         * Resets with each new level load, it is not persistent.
         */
        std::unique_ptr<SLevelSettings> m_settings;

        std::vector<std::unique_ptr<CEntity>> m_entities;

        sf::View m_defaultView;
        sf::View* m_view {&m_defaultView};
    };
}

#endif // TAILS_LEVEL_HPP
