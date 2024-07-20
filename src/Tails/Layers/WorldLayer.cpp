#include <Tails/Layers/WorldLayer.hpp>
#include <Tails/States/LevelState.hpp>
#include <Tails/Entities/Entity.hpp>

namespace tails
{
    LevelState* WorldLayer::getCurrentLevel() const
    {
        return dynamic_cast<LevelState*>(getActiveState());
    }

    LevelState* WorldLayer::openLevel(std::string levelFile)
    {
        auto result = pushState<LevelState>();
        result->loadFromFile(std::move(levelFile));
        return result;
    }
} // tails
