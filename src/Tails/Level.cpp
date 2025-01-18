#include <Tails/Level.hpp>
#include <Tails/Entity.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Vector2.hpp>
#include <Tails/Components/CameraComponent.hpp>
#include <Tails/Components/TransformComponent.hpp>
#include <Tails/LevelSubsystem.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include <LDtkLoader/Level.hpp>

namespace tails
{
    CLevel::CLevel(std::string name)
        : m_name(std::move(name))
    {}

    CLevel::CLevel(CLevel&&) noexcept = default;
    CLevel& CLevel::operator=(CLevel&&) noexcept = default;
    CLevel::~CLevel() = default;

    CEntity* CLevel::spawnEntity(
        const std::string_view className,
        const sf::Vector2f position,
        const sf::Angle rotation,
        const sf::Vector2f scale
    )
    {
        debug::print("Spawning ", className);
        return spawnEntity<CEntity>(className, position, rotation, scale);
    }

    CEntity* CLevel::spawnEntityDeferred(
        const std::string_view className,
        const sf::Vector2f position,
        const sf::Angle rotation,
        const sf::Vector2f scale
    )
    {
        return spawnEntityDeferred<CEntity>(className, position, rotation, scale);
    }

    void CLevel::finishSpawningEntity(CEntity* entity) const
    {
        if (!hasEntity(entity))
            return;

        entity->spawn();
    }

    void CLevel::destroyEntity(CEntity* entity)
    {
        if (entity)
            entity->destroy();
    }

    bool CLevel::hasEntity(CEntity* entity) const
    {
        return entity != nullptr && getEntityIterator(entity) != m_entities.end();
    }

    CLevelSubsystem& CLevel::getLevelSubsystem() const
    {
        return *getTypedOuter<CLevelSubsystem>();
    }

    CEngine& CLevel::getEngine() const
    {
        return getLevelSubsystem().getEngine();
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
        if (!camera) return false;
        
        // test pointers, not values (two different cameras with same centre and size, etc. would be the same)
        return &camera->getCameraView() == m_view;
    }

    std::optional<SHitResult> CLevel::rectangleTrace(
        const sf::FloatRect bounds,
        const std::span<CEntity*> entitiesToIgnore
    )
    {
        if (bounds.size == sf::Vector2f{0.f, 0.f})
            return std::nullopt;

        // TODO - obviously make this more optimised in the future. But it's pointless to at the moment
        for (auto& entity : m_entities)
        {
            if (!entitiesToIgnore.empty())
            {
                if (std::ranges::find_if(
                    entitiesToIgnore.begin(),
                    entitiesToIgnore.end(),
                    [&entity](auto& ignoreEntity)
                    {
                        return entity.get() == ignoreEntity;
                    }) != entitiesToIgnore.end()
                ) continue;
            }

            if (bounds.findIntersection(entity->getBounds()))
                // no idea what to do with the hit component atm so just use the entity's root component
                return std::make_optional(SHitResult{entity.get(), entity->getRootComponent()});
        }

        return std::nullopt;
    }

    const std::string& CLevel::getName() const
    {
        return m_name;
    }

    void CLevel::setParent(CLevel* parent)
    {
        if (!parent) return;

        // remove ourselves from our "old" parent
        if (auto const oldParent = getParent())
            oldParent->m_subLevels.erase(
                std::ranges::find(m_subLevels.begin(), m_subLevels.end(), this)
            );

        outer = parent;
        parent->m_subLevels.push_back(this);
    }

    CLevel* CLevel::getParent() const
    {
        return getTypedOuter<CLevel>();
    }

    bool CLevel::hasSublevel(CLevel* level) const
    {
        return std::ranges::find(m_subLevels.begin(), m_subLevels.end(), level) != m_subLevels.end();
    }

    void CLevel::addResource(const std::shared_ptr<IResource>& resource)
    {
        m_resources.emplace_back(resource);
    }

    void CLevel::preTick()
    {
        ITickable::preTick();

        for (const auto& entity : m_entities)
        {
            entity->preTick();

            if (entity->pendingCreate())
            {
                entity->unmarkForCreate();
                entity->postSpawn();
            }
        }
    }

    void CLevel::tick(const float deltaTime)
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
        const sf::FloatRect viewport {
            {getActiveCameraView().getCenter() - getActiveCameraView().getSize() / 2.f},
            {getActiveCameraView().getSize() * 2.f}
        };

        states.transform *= getTransform();
        
        target.setView(getActiveCameraView());
        //CDebug::print("Viewport left: ", viewport.position.x,
        //    ", top: ", viewport.position.y,
        //    ", right: ", viewport.size.x,
        //    ", bottom: ", viewport.size.y);
        for (auto& entity : m_entities)
        {
            // TODO - round position to integer??
            if (!entity->pendingCreate()/* && viewport.findIntersection(entity->getGlobalBounds())*/)
            {
                target.draw(*entity, states);

#ifdef TAILS_DEBUG
                if (drawEntityBounds)
                    debug::drawRect({entity->getPosition(), entity->getBounds().size});
#endif // TAILS_DEBUG
            }
        }
        
#ifdef TAILS_DEBUG
        // draw debug shapes
        drawDebug(target, states);
#endif // TAILS_DEBUG
        
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

    void CLevel::drawDebug(sf::RenderTarget& target, const sf::RenderStates& states) const
    {
        // rectangles
        for (const auto& rects = debug::getRects();
            const auto& [rect, fillColour, outlineColour, thickness] : rects)
        {
            sf::RectangleShape rectangleShape {rect.size};
            rectangleShape.setPosition(rect.position);
            rectangleShape.setFillColor(fillColour);
            rectangleShape.setOutlineColor(outlineColour);
            rectangleShape.setOutlineThickness(thickness);
            target.draw(rectangleShape, states);
        }
        
        // lines
        for (const auto& lines = debug::getLines();
            const auto& [start, end, colour, thickness] : lines)
        {
            // TODO - thickness atm is not supported as it's just two linked vertices
            std::array line {
                sf::Vertex {start, colour},
                sf::Vertex {end, colour}
            };

            target.draw(line.data(), line.size(), sf::PrimitiveType::Lines, states);
        }
        
        // circles
        for (const auto& circles = debug::getCircles();
            const auto& [
                position,
                radius,
                pointCount,
                fillColour,
                outlineColour,
                thickness
            ] : circles)
        {
            sf::CircleShape circle {radius, pointCount};
            circle.setPosition(position);
            circle.setFillColor(fillColour);
            circle.setOutlineColor(outlineColour);
            circle.setOutlineThickness(thickness);

            target.draw(circle, states);
        }

        // convex shapes
        for (const auto& convexShapes = debug::getConvexShapes();
            const auto& [
                points,
                position,
                fillColour,
                outlineColour,
                thickness
            ] : convexShapes)
        {
            sf::ConvexShape shape {points.size()};
            for (std::size_t i {0}; const auto point : points)
            {
                shape.setPoint(i, point);
                i++;
            }
            shape.setPosition(position);
            shape.setFillColor(fillColour);
            shape.setOutlineColor(outlineColour);
            shape.setOutlineThickness(thickness);

            target.draw(shape, states);
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

    CEntity* CLevel::spawnEntityImpl(std::unique_ptr<CEntity> entity, const sf::Vector2f& position, sf::Angle rotation, const sf::Vector2f& scale, bool deferred)
    {
        entity->outer = this;
        entity->setPosition(position);
        entity->setRotation(rotation);
        entity->setScale(scale);

        entity->initComponents();
        entity->loadResources();

        if (!deferred)
            entity->spawn();

        m_entities.emplace_back(std::move(entity));

        return m_entities.back().get();
    }

    CLevel::EntityIterator CLevel::getEntityIterator(CEntity* entity)
    {
        return std::ranges::find_if(m_entities.begin(), m_entities.end(),
            [entity](const auto& uniqueEntity)
            {
                return uniqueEntity.get() == entity;
            });
    }

    CLevel::ConstEntityIterator CLevel::getEntityIterator(CEntity* entity) const
    {
        return std::ranges::find_if(m_entities.begin(), m_entities.end(),
            [entity](const auto& uniqueEntity)
            {
                return uniqueEntity.get() == entity;
            });
    }
}
