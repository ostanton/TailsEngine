#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/ResourceManager.hpp>

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
         * Spawn an entity from its class.
         */
        template<typename T>
        T* spawnEntity(const sf::Vector2f& position = {0.f, 0.f}, sf::Angle rotation = sf::degrees(0.f), const sf::Vector2f& scale = {1.f, 1.f})
        {
            static_assert(std::is_base_of_v<CEntity, T>, "Failed to spawn entity, it does not derive CEntity.");
            return static_cast<T*>(spawnEntityImpl(std::make_unique<T>(), position, rotation, scale));
        }

        /**
         * Spawn an entity from its "reflected" class name.
         */
        CEntity* spawnEntity(const std::string& className, const sf::Vector2f& position = {0.f, 0.f}, sf::Angle rotation = sf::degrees(0.f), const sf::Vector2f& scale = {1.f, 1.f});

        static void destroyEntity(CEntity* entity);

        [[nodiscard]] CWorld& getWorld() const;
        [[nodiscard]] CEngine& getEngine() const;

        static bool entitiesColliding(const CEntity* entity1, const CEntity* entity2);

        [[nodiscard]] const std::string& getPath() const {return m_path;}
        [[nodiscard]] SLevelSettings& getSettings() const {return *m_settings;}

        [[nodiscard]] sf::View& getCameraView() {return m_camera;}
        [[nodiscard]] const sf::View& getCameraView() const {return m_camera;}

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

        sf::View m_camera;
    };
}

#endif // TAILS_LEVEL_HPP
