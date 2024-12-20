#include <Tails/LevelSubsystem.hpp>
#include <Tails/Level.hpp>
#include <Tails/Engine.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <ranges>

namespace tails
{
    CLevel* CLevelSubsystem::openLevel(std::string_view name, CLevel* parent)
    {
        m_levels.emplace_back(std::make_unique<CLevel>(nullptr));
        auto const result = m_levels.back().get();
        result->m_defaultView.setCenter(getEngine().getRenderView().getCenter());
        result->m_defaultView.setSize(getEngine().getRenderView().getSize());
        // load level from name

        if (parent)
        {
            result->outer = parent;
            parent->m_subLevels.push_back(result);
        }
        else
        {
            result->outer = this;
        }
        
        return result;
    }

    void CLevelSubsystem::closeLevel(CLevel* level)
    {
        if (const auto it = getLevelIterator(level); it != m_levels.end())
        {
            (*it)->markForDestroy();
            // close calls the level's entities' destroy functions, leading to nice cleanup
            (*it)->close();
        }
    }

    void CLevelSubsystem::init()
    {
        
    }

    void CLevelSubsystem::preTick()
    {
        CSubsystem::preTick();

        for (const auto& level : m_levels)
        {
            level->preTick();

            if (level->pendingCreate())
                level->unmarkForCreate();
        }
    }

    void CLevelSubsystem::tick(const float deltaTime)
    {
        for (const auto& level : m_levels)
        {
            if (!level->pendingCreate())
                level->tick(deltaTime);
        }
    }

    void CLevelSubsystem::draw(sf::RenderTarget& target, const sf::RenderStates states) const
    {
        for (const auto& level : m_levels)
        {
            if (!level->pendingCreate())
            {
                // TODO - probably has the same issues as entity components, idk haven't tested it yet
                auto tempStates = states;
                if (auto const parent = level->getParent())
                {
                    tempStates.transform *= parent->getTransform();
                }
                target.draw(*level, tempStates);
            }
        }
    }

    void CLevelSubsystem::postTick()
    {
        CSubsystem::postTick();

        for (auto it = m_levels.rbegin(); it != m_levels.rend();)
        {
            (*it)->postTick();

            if ((*it)->pendingDestroy())
                it = decltype(it)(m_levels.erase(std::next(it).base()));
            else
                ++it;
        }
    }

    CLevelSubsystem::LevelIterator CLevelSubsystem::getLevelIterator(CLevel* level)
    {
        return std::ranges::find_if(m_levels.begin(), m_levels.end(),
            [level](const std::unique_ptr<CLevel>& uniqueLevel)
            {
                return uniqueLevel.get() == level;
            });
    }

    CLevelSubsystem::ConstLevelIterator CLevelSubsystem::getLevelIterator(CLevel* level) const
    {
        return std::ranges::find_if(m_levels.begin(), m_levels.end(),
            [level](const std::unique_ptr<CLevel>& uniqueLevel)
            {
                return uniqueLevel.get() == level;
            });
    }
}
