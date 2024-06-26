#ifndef TAILS_LEVELLAYER_HPP
#define TAILS_LEVELLAYER_HPP

#include <Tails/Config.hpp>
#include <Tails/Layers/Layer.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Transform.hpp>

#include <nlohmann/json_fwd.hpp>

#include <string>
#include <vector>
#include <memory>

namespace tails
{
    class Entity;
    class EntityRegistry;
    struct Transform;

    class TAILS_API LevelLayer final : public Layer
    {
    public:
        void spawnEntity(const std::string& name, nlohmann::json& value);

        /**
         * Spawns an entity of template type
         * @tparam T Type of entity to spawn
         * @return Pointer to spawned entity
         */
        template<typename T>
        T* spawnEntity(const Transform& transform = {sf::Vector2f(0.f, 0.f), 0.f})
        {
            static_assert(std::is_base_of_v<Entity, T>, "Failed to spawn entity, template parameter does not derive Entity.");
            Debug::print("Spawning entity...");
            return static_cast<T*>(spawnEntity(std::make_unique<T>(), transform));
        }

        /**
         * Spawns an existing entity
         * @param entity Unique Pointer to entity to spawn
         * @return Pointer to moved entity
         */
        Entity* spawnEntity(std::unique_ptr<Entity> entity);
        Entity* spawnEntity(std::unique_ptr<Entity> entity, const Transform& transform);

        void loadJson(const std::string& path);

    private:
        void init(State& state) override;

        void preTick() override;
        void checkCollision(Entity* entity);
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        EntityRegistry* m_registry {nullptr};
        std::vector<std::unique_ptr<Entity>> m_entities;
    };
}

#endif // TAILS_LEVELLAYER_HPP
