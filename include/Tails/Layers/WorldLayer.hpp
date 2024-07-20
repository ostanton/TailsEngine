#ifndef TAILS_WORLDLAYER_HPP
#define TAILS_WORLDLAYER_HPP

#include <Tails/Config.hpp>
#include <Tails/Layers/Layer.hpp>

#include <string>

namespace tails
{
    class LevelState;
    class Entity;

    /**
     * Manages levels. Mostly just a level-friendly interface for Layer. Intended to only hold LevelStates.
     */
    class TAILS_API WorldLayer : public Layer
    {
    public:
        [[nodiscard]] LevelState* getCurrentLevel() const;

        /**
         * Loads a level and sets it as the current level (opens it).
         * @param levelFile
         * @return
         */
        LevelState* openLevel(std::string levelFile);

        // TODO - load a level but not open it?
    };
} // tails

#endif //TAILS_WORLDLAYER_HPP
