#ifndef TAILS_LEVELSTATE_HPP
#define TAILS_LEVELSTATE_HPP

#include <Tails/State.hpp>
#include <Tails/Entity.hpp>

#include <vector>
#include <memory>
#include <iostream>

namespace tails
{
    class LevelState final : public State
    {
    public:
        template<typename T>
        T* spawnEntity()
        {
            m_entities.push_back(std::make_unique<T>());
            Entity* resultEntity {m_entities[m_entities.size() - 1].get()};
            resultEntity->outer = this;
            resultEntity->create();
            return static_cast<T*>(resultEntity);
        }

        void destroyEntity(Entity* entity);
        void destroyEntity(const std::unique_ptr<Entity>& entity);

    private:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        std::vector<std::unique_ptr<Entity>> m_entities;
    };
}

#endif // TAILS_LEVELSTATE_HPP
