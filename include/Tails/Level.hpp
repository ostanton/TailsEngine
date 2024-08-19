#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <string>
#include <memory>
#include <vector>

namespace tails
{
    class CWorld;
    class CEntity;
    class CEngine;
    
    class TAILS_API CLevel final : public CObject, public ITickable, public sf::Drawable
    {
        friend CWorld;
        
    public:
        CLevel() = delete;
        CLevel(const CLevel&) = delete;
        CLevel(CLevel&&) = default;
        ~CLevel() override;
        CLevel& operator=(const CLevel&) = delete;
        CLevel& operator=(CLevel&&) = default;
        
        template<typename T>
        T* spawnEntity()
        {
            static_assert(std::is_base_of_v<CEntity, T>, "Failed to spawn entity, it does not derive CEntity.");
            return static_cast<T*>(spawnEntityImpl(std::make_unique<T>()));
        }

        CEntity* spawnEntity(const std::string& className);

        static void destroyEntity(CEntity* entity);

        [[nodiscard]] CWorld& getWorld() const;
        [[nodiscard]] CEngine& getEngine() const;

        static bool entitiesColliding(const CEntity* entity1, const CEntity* entity2);

        [[nodiscard]] const std::string& getPath() const {return m_path;}
        
    private:
        CLevel(std::string path);

        /**
         * Load the level from the already set .json file.
         * Essentially "reloads" it.
         */
        void load();

        void open();

        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        /**
         * Called when this level is being closed and another is opening.
         */
        void close() const;

        void checkCollision(CEntity* entity) const;

        CEntity* spawnEntityImpl(std::unique_ptr<CEntity> entity);

        std::string m_path;

        std::vector<std::unique_ptr<CEntity>> m_entities;
    };
}

#endif // TAILS_LEVEL_HPP
