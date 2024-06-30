#include <Tails/Entities/Entity.hpp>

#include <nlohmann/json.hpp>

namespace tails
{
    void Entity::destroy()
    {
        pendingDestroy = true;
        // use LevelState's destroyEntity() if we need more than this!
    }

    Entity* Entity::read(const nlohmann::json& json)
    {
        Entity* result {new Entity};
        setEntityDefaults(result, json);
        return result;
    }

    bool Entity::isCollidingWith(Entity* entity)
    {
        return getGlobalBounds().intersects(entity->getGlobalBounds());
    }

    sf::FloatRect Entity::getGlobalBounds() const
    {
        return {0.f, 0.f, 0.f, 0.f};
    }

    void Entity::setEntityDefaults(Entity* entity, const nlohmann::json& json)
    {
        if (!entity) return;

        for (auto& [key, value] : json.items())
        {
            if (key == "position")
            {
                setPosition(value["x"].get<float>(), value["y"].get<float>());
            }

            if (key == "rotation")
            {
                setRotation(value.get<float>());
            }

            if (key == "scale")
            {
                setScale(value["x"].get<float>(), value["y"].get<float>());
            }
        }
    }
}
