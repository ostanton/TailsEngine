#pragma once
#include <SFML/Graphics/Drawable.hpp>

#include "Level.h"
#include "Obj.h"
#include "TailsEngine/Core/Entity.h"

namespace sf
{
class Event;
}

namespace tails
{
class InputManager;
class GameInstance;
}

namespace tails
{
/**
 * \brief A class to easily switch between level classes and spawn entities. This isn't strictly needed,
 * but helps to segment things.
 */
class World final : public Object, public sf::Drawable
{
    friend GameInstance;
    friend Level;
    
public:
    void construct() override;
    void create();
    
    /**
     * \brief The currently loaded level
     */
    unique_ptr<Level> currentLevel;

    /**
     * \brief Gets the current level (that is "in play")
     * \return Pointer to the level
     */
    Level* getCurrentLevel() const;

    GameInstance& getGameInstance() const;
    Viewport& getViewport() const;

    void setViewCameraPosition(const sf::Vector2f& position) const;

    /**
     * \brief Creates a level object and loads it into the level's vector
     * \tparam LevelT The level type to load
     * \return Pointer to the created level object
     * \remarks TODO - have .json file as input for Level object to load
     */
    template<typename LevelT>
    LevelT* createAndOpenLevel()
    {
        static_assert(std::is_base_of_v<Level, LevelT>, "Cannot create non-Level class");
        
        auto resultLevel = newObject<LevelT>(this);
        m_levelToOpen.reset(resultLevel);

        return dynamic_cast<LevelT*>(resultLevel);
    }

    void openTargetLevel();

protected:
    unique_ptr<Level> m_levelToOpen;
    
    /**
     * \brief Called every frame
     * \param deltaTime Time since last frame
     */
    void update(float deltaTime);
    void processInput(sf::Event& e);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setupData() override;
    void cleanupData() override;
};

}
