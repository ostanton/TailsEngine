#include <Tails/World.hpp>
#include <Tails/Level.hpp>
#include <Tails/Engine.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    void CWorld::openLevel(std::string path)
    {
        // cannot use make_unique unless CLevel(string) constructor is public
        // TODO:
        // maybe change this so we check for if m_path is set, and delay this until postTick?
        // then we only have 2 levels open for the duration of that function.
        // or not have the level to load, just the path to load??
        m_levelToLoad.reset(new CLevel(std::move(path)));
        m_levelToLoad->outer = this;
    }

    CEngine& CWorld::getEngine() const
    {
        return *dynamic_cast<CEngine*>(outer);
    }

    void CWorld::setDefaultLevel(std::string path)
    {
        // cannot use make_unique unless CLevel(string) constructor is public
        m_currentLevel.reset(new CLevel(std::move(path)));
        m_currentLevel->outer = this;
    }

    void CWorld::preTick()
    {
        ITickable::preTick();

        m_currentLevel->preTick();
    }

    void CWorld::tick(float deltaTime)
    {
        m_currentLevel->tick(deltaTime);
    }

    void CWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(*m_currentLevel, states);
    }

    void CWorld::postTick()
    {
        ITickable::postTick();

        m_currentLevel->postTick();

        if (m_levelToLoad)
        {
            m_currentLevel->onClose();
            m_currentLevel = std::move(m_levelToLoad);
            m_levelToLoad.reset();
        }
    }
}
