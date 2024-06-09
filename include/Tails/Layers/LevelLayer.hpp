#ifndef TAILS_LEVELLAYER_HPP
#define TAILS_LEVELLAYER_HPP

#include <Tails/Layers/Layer.hpp>

#include <string>
#include <vector>
#include <memory>

namespace tails
{
    class Entity;

    class LevelLayer : public Layer
    {
    public:
        void spawnEntity(const std::string& name);

    protected:
        void loadJson(const std::string& path);

        std::vector<std::unique_ptr<Entity>> m_entities;
    };
}

#endif // TAILS_LEVELLAYER_HPP