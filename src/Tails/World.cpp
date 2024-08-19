#include <Tails/World.hpp>
#include <Tails/Level.hpp>
#include <Tails/Engine.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CLevel* CWorld::openLevel(std::string path)
    {
        m_openLevels.emplace_back(new CLevel(std::move(path)));
        CLevel* result {m_openLevels.back().get()};
        result->outer = this;

        result->open();

        return result;
    }

    bool CWorld::closeLevel(CLevel* level)
    {
        if (auto it = std::find_if(m_openLevels.begin(), m_openLevels.end(),
            [&](auto& uniqueLevel)
            {
                return uniqueLevel.get() == level;
            }); it != m_openLevels.end())
        {
            level->markForDestroy();
            level->close();
            return true;
        }

        return false;
    }

    CEngine& CWorld::getEngine() const
    {
        return *dynamic_cast<CEngine*>(outer);
    }

    CLevel* CWorld::getLevel(size_t index) const
    {
        if (index >= m_openLevels.size()) return nullptr;
        
        return m_openLevels[index].get();
    }

    void CWorld::preTick()
    {
        ITickable::preTick();

        for (auto& level : m_openLevels)
        {
            level->preTick();
        }
    }

    void CWorld::tick(float deltaTime)
    {
        for (auto& level : m_openLevels)
        {
            level->tick(deltaTime);
        }
    }

    void CWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& level : m_openLevels)
        {
            target.draw(*level, states);
        }
    }

    void CWorld::postTick()
    {
        ITickable::postTick();

        for (auto it = m_openLevels.rbegin(); it != m_openLevels.rend();)
        {
            (*it)->postTick();

            if ((*it)->pendingDestroy())
            {
                it = decltype(it)(m_openLevels.erase(std::next(it).base()));
            }
            else
                ++it;
        }
    }
}
