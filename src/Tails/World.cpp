#include <Tails/World.hpp>
#include <Tails/Level.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Vector2.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <LDtkLoader/World.hpp>

namespace tails
{
    CWorld::~CWorld() = default;

    CLevel& CWorld::openLevel(const std::string& name, const bool closePrevious /* = true */)
    {
        if (m_openLevels.empty() || !closePrevious)
        {
            m_openLevels.emplace_back(m_world ? &m_world->getLevel(name) : nullptr);
        }
        else if (closePrevious)
        {
            m_openLevels[m_openLevels.size() - 1] = CLevel(nullptr);
        }
        
        CLevel& result {m_openLevels.back()};
        result.outer = this;
        result.m_defaultView.setCenter(getEngine().getRenderView().getCenter());
        result.m_defaultView.setSize(getEngine().getRenderView().getSize());

        return result;
    }

    bool CWorld::closeLevel(CLevel* level)
    {
        if (const auto it = std::ranges::find_if(m_openLevels.begin(), m_openLevels.end(),
            [&](auto& uniqueLevel)
            {
                return &uniqueLevel == level;
            }); it != m_openLevels.end())
        {
            level->markForDestroy();
            level->close();
            return true;
        }

        return false;
    }

    bool CWorld::closeLevel(const size_t index)
    {
        if (index >= m_openLevels.size())
            return false;

        m_openLevels[index].markForDestroy();
        m_openLevels[index].close();
        return true;
    }

    CEngine& CWorld::getEngine() const
    {
        return *getTypedOuter<CEngine>();
    }

    CLevel* CWorld::getLevel(const size_t index)
    {
        if (index >= m_openLevels.size()) return nullptr;
        
        return &m_openLevels[index];
    }

    const CLevel* CWorld::getLevel(const size_t index) const
    {
        if (index >= m_openLevels.size()) return nullptr;
        
        return &m_openLevels[index];
    }

    CLevel* CWorld::getLevel(const std::string_view name)
    {
        for (auto& level : m_openLevels)
        {
            if (level.getName() == name)
                return &level;
        }

        return nullptr;
    }

    const CLevel* CWorld::getLevel(const std::string_view name) const
    {
        for (auto& level : m_openLevels)
        {
            if (level.getName() == name)
                return &level;
        }

        return nullptr;
    }

    CWorld::CWorld() = default;

    void CWorld::setLDtkWorld(const ldtk::World* world)
    {
        m_world = world;
    }

    void CWorld::preTick()
    {
        ITickable::preTick();

        for (auto& level : m_openLevels)
        {
            level.preTick();
        }
    }

    void CWorld::tick(const float deltaTime)
    {
        for (auto& level : m_openLevels)
        {
            level.tick(deltaTime);
        }
    }

    void CWorld::draw(sf::RenderTarget& target, const sf::RenderStates states) const
    {
        for (auto& level : m_openLevels)
        {
            target.draw(level, states);
        }
    }

    void CWorld::postTick()
    {
        ITickable::postTick();

        for (auto it = m_openLevels.rbegin(); it != m_openLevels.rend();)
        {
            it->postTick();

            if (it->pendingDestroy())
            {
                it = decltype(it)(m_openLevels.erase(std::next(it).base()));
            }
            else
                ++it;
        }
    }
}
