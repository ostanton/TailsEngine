#include <Tails/LevelSubsystem.hpp>
#include <Tails/Level.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Level/LDtkLoadParams.hpp>
#include <Tails/ResourceManager.hpp>
#include <Tails/Resources/Texture.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <LDtkLoader/Project.hpp>

#include <ranges>

namespace tails
{
    CLevel* CLevelSubsystem::loadLDtkLevel(const SLDtkLoadParams& params, CLevel* parent, const bool closeOthers)
    {
        try
        {
            ldtk::Project project;
            project.loadFromFile(params.path.string());
            
            const auto& world {
                params.world.empty() ? project.getWorld() : project.getWorld(params.world)
            };
            const auto& ldtkLevel = world.getLevel(params.level);

            auto level = std::make_unique<CLevel>(ldtkLevel.name);
            if (!project.allTilesets().empty())
                level->addResource(CResourceManager::loadResource<CTexture>(project.getTileset(0).path));
            level->setPosition({static_cast<float>(ldtkLevel.position.x), static_cast<float>(ldtkLevel.position.y)});
            
            for (const auto& layer = ldtkLevel.getLayer(params.layer);
                const auto& entity : layer.allEntities())
            {
                const sf::Vector2f position {
                    static_cast<float>(entity.getPosition().x),
                    static_cast<float>(entity.getPosition().y)
                };
                // TODO - rotation & scale
                level->spawnEntityDeferred(entity.getName(), position);
            }

            for (const auto& entity : level->getEntities())
            {
                level->finishSpawningEntity(entity.get());
            }

            return setupLevel(std::move(level), parent, closeOthers);
        }
        catch (const std::invalid_argument& e)
        {
            debug::exception("Failed to load LDtk project: ", e.what());
            return nullptr;
        }
        catch (...)
        {
            debug::exception("Unknown exception, rethrowing");
            throw;
        }
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

    void CLevelSubsystem::closeAllLevels()
    {
        for (const auto& level : m_levels)
        {
            closeLevel(level.get());
        }
    }

    void CLevelSubsystem::closeAllLevelsExcept(const CLevel* exceptionLevel)
    {
        for (const auto& level : m_levels)
        {
            if (level.get() == exceptionLevel)
                continue;

            closeLevel(level.get());
        }
    }

    CLevel* CLevelSubsystem::setupLevel(std::unique_ptr<CLevel> level, CLevel* parent, const bool closeOthers)
    {
        if (closeOthers)
            closeAllLevels();
        
        m_levels.emplace_back(std::move(level));
        auto const result = m_levels.back().get();
        result->m_defaultView.setCenter(getEngine().getRenderView().getCenter());
        result->m_defaultView.setSize(getEngine().getRenderView().getSize());

        if (parent)
        {
            result->outer = parent;
            result->m_subLevels.emplace_back(result);
        }
        else
        {
            result->outer = this;
        }

        return result;
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
            // TODO - level is invalid memory here when loading more than two at once!
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
