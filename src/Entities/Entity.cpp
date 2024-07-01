#include <Tails/Entities/Entity.hpp>
#include <Tails/Debug.hpp>

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

    bool Entity::isCollidingWith(Entity* entity) const
    {
        return getGlobalBounds().intersects(entity->getGlobalBounds());
    }

    sf::FloatRect Entity::getGlobalBounds() const
    {
        return {0.f, 0.f, 0.f, 0.f};
    }

    void Entity::setTransform(const Transform& transform)
    {
        Debug::print(transform.toString());
        setPosition(transform.position);
        setRotation(transform.rotation);
        setScale(transform.scale);
    }

    Transform Entity::makeTransform() const
    {
        return {getPosition(), getRotation(), getScale()};
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
