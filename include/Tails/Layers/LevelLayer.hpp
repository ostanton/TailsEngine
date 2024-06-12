#ifndef TAILS_LEVELLAYER_HPP
#define TAILS_LEVELLAYER_HPP

#include <Tails/Layers/Layer.hpp>
#include <Tails/Debug.hpp>

#include <nlohmann/json_fwd.hpp>

#include <string>
#include <vector>
#include <memory>

namespace tails
{
    class Entity;
    class EntityRegistry;

    class TAILS_API LevelLayer : public Layer
    {
    public:
        void spawnEntity(const std::string& name, const nlohmann::json& json);

        /**
         * Spawns an entity of template type
         * @tparam T Type of entity to spawn
         * @return Pointer to spawned entity
         */
        template<typename T>
        T* spawnEntity() // transform or something as input
        {
            static_assert(std::is_base_of_v<Entity, T>, "Failed to spawn entity, template parameter does not derive Entity.");
            Debug::print("Spawning entity...");
            std::unique_ptr<Entity> resultEntity {std::make_unique<T>()};
            // could just do an in-place make_unique, but we will probably want to set some properties of entity first!
            return static_cast<T*>(spawnEntity(std::move(resultEntity)));
        }

        /**
         * Spawns an existing entity
         * @param entity Unique Pointer to entity to spawn
         * @return Pointer to moved entity
         */
        Entity* spawnEntity(std::unique_ptr<Entity> entity);

    protected:
        void init(State& state) override;
        void loadJson(const std::string& path);

        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        EntityRegistry* m_registry {nullptr};
        std::vector<std::unique_ptr<Entity>> m_entities;
    };
}

#endif // TAILS_LEVELLAYER_HPP
