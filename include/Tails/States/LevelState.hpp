#ifndef TAILS_LEVELSTATE_HPP
#define TAILS_LEVELSTATE_HPP

#include <Tails/Config.hpp>
#include <Tails/States/State.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class Entity;
    class WorldLayer;

    class TAILS_API LevelState final : public State
    {
        friend WorldLayer;

    public:
        template<typename T>
        T* spawnEntity()
        {
            static_assert(std::is_base_of_v<Entity, T>, "Failed to spawn entity, it does not derive Entity.");
            auto result = std::make_unique<T>();
            result->outer = this;
            result->create();
            return static_cast<T*>(spawnEntity(std::move(result)));
        }

        Entity* spawnEntity(std::unique_ptr<Entity> entity);

        [[nodiscard]] WorldLayer& getWorld() const;

        /**
         * Get the first found entity of the specified type
         * @tparam T Entity type
         * @return Found entity or nullptr if not found
         */
        template<typename T>
        [[nodiscard]] T* getEntityOfType() const
        {
            for (auto& entity : m_entities)
                if (auto castedEntity = dynamic_cast<T*>(entity.get()))
                    return castedEntity;

            return nullptr;
        }

        template<typename T>
        [[nodiscard]] std::vector<T*> getAllEntitiesOfType() const
        {
            std::vector<T*> foundEntities;

            for (auto& entity : m_entities)
                if (auto castedEntity = dynamic_cast<T*>(entity.get()))
                    foundEntities.push_back(castedEntity);

            return foundEntities;
        }

        void destroyEntity(Entity* entity);

    private:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void postTick() override;

        void loadFromFile(std::string levelFile);

        std::vector<std::unique_ptr<Entity>> m_entities;
    };
} // tails

#endif //TAILS_LEVELSTATE_HPP
