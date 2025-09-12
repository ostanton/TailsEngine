#include <Tails/World/Level.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/ActorRegistry.hpp>
#include <Tails/World/CameraActor.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Renderer/Vertex.hpp>
#include <Tails/World/Camera.hpp>
#include <Tails/World/Components/CameraComponent.hpp>
#include <Tails/Maths/SAT.hpp>

#include <algorithm>
#include <unordered_set>

namespace tails
{
    void CLevelRenderBatch::addItem(
        const int layer,
        const STransform2D& worldTransform,
        const SColour colour,
        const SVector2f size,
        std::shared_ptr<CTexture> texture
    )
    {
        std::vector vertices {
            SVertex {
                .position = {},
                .colour = colour,
                .texCoord = {},
            },
            SVertex {
                .position = {size.x, 0.f},
                .colour = colour,
                .texCoord = {1.f, 0.f},
            },
            SVertex {
                .position = {0.f, size.y},
                .colour = colour,
                .texCoord = {0.f, 1.f},
            },
            SVertex {
                .position = size,
                .colour = colour,
                .texCoord = {1.f, 1.f},
            },
        };
        const int indices[6] = {
            0, 1, 2,
            1, 3, 2,
        };
        addItem(
            layer,
            worldTransform,
            std::move(vertices),
            std::vector<int> {std::begin(indices), std::end(indices)},
            std::move(texture)
        );
    }

    void CLevelRenderBatch::addItem(
        const int layer,
        const STransform2D& worldTransform,
        std::vector<SVertex> vertices,
        std::shared_ptr<CTexture> texture
    )
    {
        std::vector<int> indices;
        indices.reserve(vertices.size() * 3);

        // generate the indices in anti-clockwise winding order
        for (usize i {0}; i < vertices.size() - 1; i++)
        {
            indices.emplace_back(0);
            indices.emplace_back(static_cast<int>(i));
            indices.emplace_back(static_cast<int>(i + 1));
        }

        addItem(layer, worldTransform, std::move(vertices), std::move(indices), std::move(texture));
    }

    void CLevelRenderBatch::addItem(
        const int layer,
        const STransform2D& worldTransform,
        std::vector<SVertex> vertices,
        std::vector<int> indices,
        std::shared_ptr<CTexture> texture
    )
    {
        for (auto& vertex : vertices)
            vertex.position = worldTransform.transformPoint(vertex.position);

        m_items.emplace_back(std::move(vertices), std::move(indices), std::move(texture), layer);
    }

    CLevel::CLevel() = default;

    CLevel::CLevel(ActorsVector&& actors)
        : m_actors(std::move(actors))
    {}

    CLevel::~CLevel() = default;

    void CLevel::finishLoad()
    {
        if (!m_activeCamera)
        {
            setActiveCamera(
                spawnActor<CCameraActor>({
                    {0.f, 0.f},
                    0.f,
                    {1.f, 1.f}
                })->cameraComponent
            );
        }
    }

    CActor* CLevel::spawnActor(
        std::unique_ptr<CActor> actor,
        const STransform2D& transform,
        const int layer
    )
    {
        auto const result = spawnActorDeferred(std::move(actor), transform, layer);
        if (!result)
            return nullptr;
        
        finishActorSpawn(result);
        return result;
    }

    CActor* CLevel::spawnActor(
        const CString& name,
        const STransform2D& transform,
        const int layer
    )
    {
        return spawnActor(impl::allocateActor(name), transform, layer);
    }

    CActor* CLevel::spawnActorDeferred(
        const CString& name,
        const STransform2D& transform,
        const int layer
    )
    {
        return spawnActorDeferred(impl::allocateActor(name), transform, layer);
    }

    CActor* CLevel::spawnActorDeferred(
        std::unique_ptr<CActor> actor,
        const STransform2D& transform,
        const int layer
    )
    {
        m_actors.emplace_back(std::move(actor));
        auto& result = *m_actors.back();
        result.layer = layer;
        result.m_owningLevel = std::static_pointer_cast<CLevel>(shared_from_this());
        result.setTransform(transform);
        return &result;
    }

    void CLevel::finishActorSpawn(CActor* actor) const
    {
        if (!actor || getActorIterator(actor) == m_actors.end())
            return;

        actor->onInitComponents();
        actor->onSpawn();
    }

    SVector2f CLevel::worldToScreen(const SVector2f worldPoint) const noexcept
    {
        return m_activeCamera->worldToView(worldPoint);
    }

    SFloatRect CLevel::worldToScreen(const SFloatRect& worldRect) const noexcept
    {
        return m_activeCamera->worldToView(worldRect);
    }

    SFloatOrientedRect CLevel::worldToScreen(const SFloatOrientedRect& worldRect) const noexcept
    {
        return m_activeCamera->worldToView(worldRect);
    }

    STransform2D CLevel::worldToScreen(const STransform2D& worldTransform) const noexcept
    {
        return m_activeCamera->worldToView(worldTransform);
    }

    SVector2f CLevel::screenToWorld(const SVector2f screenPoint) const noexcept
    {
        return m_activeCamera->viewToWorld(screenPoint);
    }

    SFloatRect CLevel::screenToWorld(const SFloatRect& screenRect) const noexcept
    {
        return m_activeCamera->viewToWorld(screenRect);
    }

    SFloatOrientedRect CLevel::screenToWorld(const SFloatOrientedRect& screenRect) const noexcept
    {
        return m_activeCamera->viewToWorld(screenRect);
    }

    STransform2D CLevel::screenToWorld(const STransform2D& screenTransform) const noexcept
    {
        return m_activeCamera->viewToWorld(screenTransform);
    }

    void CLevel::setActiveCamera(CCameraComponent* cameraComponent)
    {
        if (!cameraComponent)
        {
            // TODO - Fallback to default camera
            return;
        }

        m_activeCamera = &cameraComponent->camera;
        m_activeCameraComponent = cameraComponent;
    }

    void CLevel::setActiveCamera(SCamera& camera)
    {
        m_activeCamera = &camera;
        m_activeCameraComponent = nullptr;
    }

    SCamera& CLevel::getActiveCamera() noexcept
    {
        return *m_activeCamera;
    }

    const SCamera& CLevel::getActiveCamera() const noexcept
    {
        return *m_activeCamera;
    }

    CCameraComponent* CLevel::getActiveCameraComponent() noexcept
    {
        return m_activeCameraComponent;
    }

    const CCameraComponent* CLevel::getActiveCameraComponent() const noexcept
    {
        return m_activeCameraComponent;
    }

    void CLevel::onTick(const float deltaSeconds)
    {
        for (usize i {0}; i < m_actors.size(); i++)
        {
            m_actors[i]->onTick(deltaSeconds);
        }

        // collision pass

        /**
         * This all seems rather inefficient at first glance, however I'm leaving it like this
         * until problems start to arise with performance. Chances are they never will, but you never know.
         */

        m_collisionManager.beginCollisions();
        m_debugSATShapes.clear();

        // track multiple components colliding in a single frame, only call onStartCollision once if so
        std::set<std::pair<CActor*, CActor*>> actorsStartedCollision;

        // track which components are colliding for their debug SAT shape to be rendered
        std::unordered_set<CComponent*> collidingComponents;

        for (usize i {0}; i < m_actors.size(); i++)
        {
            auto const actorA = m_actors[i].get();
            for (usize j {i + 1}; j < m_actors.size(); j++)
            {
                auto const actorB = m_actors[j].get();

                // test component SAT shapes
                for (const auto& compA : actorA->m_components)
                {
                    if (compA->collisionType == ECollisionType::None)
                        continue;

                    for (const auto& compB : actorB->m_components)
                    {
                        if (compB->collisionType == ECollisionType::None)
                            continue;

                        if (compA->getSATShape().intersects(compB->getSATShape()))
                        {
                            m_collisionManager.registerCollision(compA.get(), compB.get());

                            // call onStartCollision if the collision just started this frame
                            if (m_collisionManager.didCollisionStart(compA.get(), compB.get()))
                            {
                                compA->onStartCollision(compB.get());
                                compB->onStartCollision(compA.get());

                                // make sure we don't call the owning actor's onStartCollision if
                                // another component from the same actor is already colliding with something
                                if (m_collisionManager.didCollisionStart(actorA, actorB) &&
                                    !m_collisionManager.hasActorCollisionStarted(actorA, actorB))
                                {
                                    m_collisionManager.markActorCollisionStarted(actorA, actorB);
                                    actorA->onStartCollision(actorB, compB.get());
                                    actorB->onStartCollision(actorA, compA.get());
                                }
                            }

                            compA->onCollision(compB.get());
                            compB->onCollision(compA.get());

                            collidingComponents.insert(compA.get());
                            collidingComponents.insert(compB.get());

                            actorA->onCollision(actorB, compB.get());
                            actorB->onCollision(actorA, compA.get());
                        }
                    }
                }
            }
        }

        m_collisionManager.forEndedComponentCollisions([](CComponent* compA, CComponent* compB)
        {
            compA->onEndCollision(compB);
            compB->onEndCollision(compA);
        });

        m_collisionManager.forEndedActorCollisions([](CActor* actorA, CActor* actorB)
        {
            actorA->onEndCollision(actorB, nullptr);
            actorB->onEndCollision(actorA, nullptr);
        });

        m_collisionManager.endCollisions();

        // add the debug SAT shapes for rendering
        for (const auto& actor : m_actors)
        {
            for (const auto& comp : actor->m_components)
            {
                m_debugSATShapes.emplace_back(
                    comp->getSATShape(),
                    collidingComponents.contains(comp.get()) // colliding or not
                );
            }
        }
    }

    void CLevel::onRender() const
    {
        CLevelRenderBatch renderBatch;
        for (const auto& actor : m_actors)
        {
            actor->onRender(renderBatch);
        }

        // sort the render items from the lowest layer to the highest
        std::ranges::sort(renderBatch.m_items, {}, &CLevelRenderBatch::SItem::layer);

        for (const auto& item : renderBatch.m_items)
        {
            auto vertices = item.vertices;
            for (auto& vertex : vertices)
            {
                vertex.position = worldToScreen(vertex.position);
            }
            render::geometry(vertices, item.indices, item.texture);
        }

        // debug SAT shape rendering
        for (const auto& [shape, colliding] : m_debugSATShapes)
        {
            // get the vertices in screen space
            std::vector<SVector2f> screenPositions;
            screenPositions.reserve(shape.size());
            for (const auto vertex : shape)
            {
                screenPositions.emplace_back(worldToScreen(vertex));
            }
            render::debugLines(screenPositions, colliding ? SFloatColour::green : SFloatColour::white);
        }
    }

    void CLevel::cleanupActors()
    {
        // TODO - could improve with std::remove_if
        for (auto it {m_actors.rbegin()}; it != m_actors.rend();)
        {
            if (it->get()->flags.isBitSet(CActor::PendingKill))
            {
                m_collisionManager.cleanupCollisions(it->get());
                it = decltype(it)(m_actors.erase(std::next(it).base()));
            }
            else
                ++it;
        }
    }

    std::vector<CComponent*> CLevel::getCollisionsFor(const CComponent* component) const noexcept
    {
        return m_collisionManager.getCollisionsFor(component);
    }

    std::vector<CActor*> CLevel::getCollisionsFor(const CActor* actor) const noexcept
    {
        return m_collisionManager.getCollisionsFor(actor);
    }

    bool CLevel::areColliding(const CComponent* compA, const CComponent* compB) const noexcept
    {
        return m_collisionManager.areColliding(compA, compB);
    }

    bool CLevel::areColliding(const CActor* actorA, const CActor* actorB) const noexcept
    {
        return m_collisionManager.areColliding(actorA, actorB);
    }

    CLevel::ActorIterator CLevel::getActorIterator(const CActor* actor)
    {
        return std::find_if(m_actors.begin(), m_actors.end(),
            [actor](const std::unique_ptr<CActor>& uniqueActor)
            {
                return actor == uniqueActor.get();
            });
    }

    CLevel::ConstActorIterator CLevel::getActorIterator(const CActor* actor) const
    {
        return std::find_if(m_actors.begin(), m_actors.end(),
            [actor](const std::unique_ptr<CActor>& uniqueActor)
            {
                return actor == uniqueActor.get();
            });
    }

    const CLevel::ActorsVector& CLevel::getActors() const
    {
        return m_actors;
    }

    EAssetType CLevel::getAssetType() const noexcept
    {
        return EAssetType::Level;
    }

    void CLevel::initActors() const
    {
        // TODO - two passes for this? one for initialising components, the second for onSpawn?
        for (const auto& actor : m_actors)
        {
            actor->onInitComponents();
            actor->onSpawn();
        }
    }

    bool CLevel::containsActor(const CActor* actor) const
    {
        return getActorIterator(actor) != m_actors.end();
    }
}
