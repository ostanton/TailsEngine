#include <Tails/World.hpp>
#include <Tails/Level.hpp>
#include <Tails/Engine.hpp>
#include <Tails/LevelSettings.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Vector2.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CLevel* CWorld::openLevel(std::string path, std::unique_ptr<SLevelSettings> settings)
    {
        m_openLevels.emplace_back(new CLevel(std::move(path)));
        CLevel* result {m_openLevels.back().get()};
        result->outer = this;
        result->setSettings(std::move(settings));
        result->m_defaultView.setCenter(getEngine().getRenderView().getCenter());
        result->m_defaultView.setSize(getEngine().getRenderView().getSize());

        result->open();

        CDebug::printf("Opened level path \"{}\"", path);

        return result;
    }

    bool CWorld::closeLevel(CLevel* level)
    {
        if (const auto it = std::find_if(m_openLevels.begin(), m_openLevels.end(),
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

    bool CWorld::closeLevel(size_t index) const
    {
        if (index >= m_openLevels.size())
            return false;

        m_openLevels[index]->markForDestroy();
        m_openLevels[index]->close();
        return true;
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
