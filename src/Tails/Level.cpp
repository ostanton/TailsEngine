#include <Tails/Level.hpp>
#include <Tails/World.hpp>
#include <Tails/Entity.hpp>
#include <Tails/Engine.hpp>
#include <Tails/LevelSettings.hpp>
#include <Tails/Vector2.hpp>
#include <Tails/CameraComponent.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CLevel::~CLevel() = default;

    CEntity* CLevel::spawnEntity(std::string_view className, const sf::Vector2f& position, sf::Angle rotation, const sf::Vector2f& scale)
    {
        return spawnEntity<CEntity>(className, position, rotation, scale);
    }

    void CLevel::destroyEntity(CEntity* entity)
    {
        if (entity)
            entity->destroy();
    }

    CWorld& CLevel::getWorld() const
    {
        return *dynamic_cast<CWorld*>(outer);
    }

    CEngine& CLevel::getEngine() const
    {
        return getWorld().getEngine();
    }

    bool CLevel::entitiesColliding(const CEntity* entity1, const CEntity* entity2)
    {
        // check for if entity2 is valid resides in colliding()
        if (!entity1) return false;
        
        return entity1->colliding(entity2);
    }

    void CLevel::setActiveCamera(CCameraComponent* camera)
    {
        if (!camera) return;

        m_view = &camera->getCameraView();
    }

    void CLevel::setActiveCameraView(sf::View& view)
    {
        m_view = &view;
    }

    const sf::View& CLevel::getActiveCameraView() const
    {
        return *m_view;
    }

    bool CLevel::isCameraActive(const CCameraComponent* camera) const
    {
        // TODO - test equality of views
        return &camera->getCameraView() == m_view;
    }

    CLevel::CLevel(std::string path)
        : m_path(std::move(path))
    {
    }

    void CLevel::open()
    {
        // TODO - replace with loading from json, the name specified there.
        // If not specified, the file name or something.

        // TODO - use default settings if level settings does not exist!!
        if (m_path.empty())
            getSettings().name = "none";
    }

    void CLevel::setSettings(std::unique_ptr<SLevelSettings> settings)
    {
        m_settings = std::move(settings);
    }

    void CLevel::preTick()
    {
        ITickable::preTick();

        for (auto& entity : m_entities)
        {
            entity->preTick();

            if (entity->pendingCreate())
            {
                entity->unmarkForCreate();
                entity->postSpawn();
            }
        }
    }

    void CLevel::tick(float deltaTime)
    {
        // normal for loop instead of range-based because I think the iterator gets invalidated when emplacing
        // for spawning entities whilst iterating! This works, however.
        for (size_t i {0}; i < m_entities.size(); i++)
        {
            if (!m_entities[i]->pendingCreate())
            {
                m_entities[i]->tick(deltaTime);

                checkCollision(m_entities[i].get());
            }
        }
    }

    void CLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        sf::FloatRect viewport {
            {getActiveCameraView().getCenter() - getActiveCameraView().getSize() / 2.f},
            {getActiveCameraView().getSize()}
        };
        
        target.setView(getActiveCameraView());
        for (auto& entity : m_entities)
        {
            // TODO - round position to integer??
            if (!entity->pendingCreate()) //&& viewport.findIntersection(entity->getGlobalBounds()))
            {
                target.draw(*entity, states);
            }
        }
        target.setView(target.getDefaultView());
    }

    void CLevel::postTick()
    {
        ITickable::postTick();

        for (auto it = m_entities.rbegin(); it != m_entities.rend();)
        {
            it->get()->postTick();

            // not really any idea if this works, found it on stack overflow or something
            if (it->get()->pendingDestroy())
                it = decltype(it)(m_entities.erase(std::next(it).base()));
            else
                ++it;
        }
    }

    void CLevel::close() const
    {
        if (!m_entities.empty())
        {
            for (auto& entity : m_entities)
            {
                entity->destroy();
            }
        }
    }

    void CLevel::checkCollision(CEntity* entity) const
    {
        if (!entity) return;
        
        for (auto& entity2 : m_entities)
        {
            if (!entity2->pendingCreate() && entity2.get() != entity)
            {
                if (entity->colliding(entity2.get()))
                    entity->collision(*entity2);
            }
        }
    }

    CEntity* CLevel::spawnEntityImpl(std::unique_ptr<CEntity> entity, const sf::Vector2f& position, sf::Angle rotation, const sf::Vector2f& scale)
    {
        entity->setPosition(position);
        entity->setRotation(rotation);
        entity->setScale(scale);

        entity->initComponents();
        entity->loadResources(resourceManager);
        entity->spawn();

        m_entities.emplace_back(std::move(entity));

        return m_entities.back().get();
    }
}
