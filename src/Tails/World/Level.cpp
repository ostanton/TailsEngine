#include <Tails/World/Level.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/ActorRegistry.hpp>
#include <Tails/World/Layer.hpp>
#include <Tails/World/CameraActor.hpp>
#include <Tails/Renderer/Renderer.hpp>

#include <algorithm>

#include "Tails/Debug.hpp"
#include "Tails/World/Components/CameraComponent.hpp"

namespace tails
{
    CLevel::CLevel() = default;

    CLevel::CLevel(ActorsVector&& actors)
        : m_actors(std::move(actors))
    {}

    CLevel::CLevel(ActorsVector&& actors, LayersMap&& layers)
        : m_layers(std::move(layers)), m_actors(std::move(actors))
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
        m_layers[layer].m_actors.push_back(&result);
        result.m_layer = layer;
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

    void CLevel::setActorLayer(CActor* actor, const int layer)
    {
        // remove actor from its current layer
        if (auto const layerPtr = getLayerFromActor(actor))
            layerPtr->removeActor(actor);

        // add actor to target layer
        m_layers[layer].addActor(actor);
        actor->m_layer = layer;
    }

    STransform2D CLevel::worldToScreen(const STransform2D& worldTransform) const
    {
        return m_activeCamera->worldToView(worldTransform);
    }

    SVector2f CLevel::screenToWorld(const SVector2f screenPoint) const
    {
        const auto resolution = render::getResolution();

        // Move origin to camera centre
        const auto relative = screenPoint - resolution / 2.f;

        // Apply inverse rotation
        const double cosA {std::cos(-m_activeCamera->rotation.asRadians())};
        const double sinA {std::sin(-m_activeCamera->rotation.asRadians())};

        SVector2d unrotated = {
            relative.x * cosA - relative.y * sinA,
            relative.x * sinA + relative.y * cosA
        };

        // Undo zoom
        unrotated /= m_activeCamera->zoom;

        return SVector2f {unrotated + m_activeCamera->position};
    }

    void CLevel::setActiveCamera(CCameraComponent* cameraComponent)
    {
        // TODO - I don't think we want to rely on a valid camera component to be the active camera
        // should probably only rely on a valid SCamera object (or pointer)
        if (!cameraComponent)
        {
            // Fallback to default camera
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

    CCameraComponent * CLevel::getActiveCameraComponent() noexcept
    {
        return m_activeCameraComponent;
    }

    const CCameraComponent* CLevel::getActiveCameraComponent() const noexcept
    {
        return m_activeCameraComponent;
    }

    void CLevel::onTick(const float deltaSeconds)
    {
        for (auto& [id, layer] : m_layers)
        {
            layer.onTick(deltaSeconds);
        }
    }

    void CLevel::onRender() const
    {
        CLevelRenderBatch renderBatch;
        // TODO - render in camera view or something idk
        for (const auto& [id, layer] : m_layers)
        {
            layer.onRender(renderBatch);
        }

        for (const auto& item : renderBatch.items)
        {
            if (item.texture)
            {
                render::texture(
                   item.texture,
                   worldToScreen(item.transform),
                   item.size,
                   item.colour
               );
            }
            else
            {
                render::quad(
                   worldToScreen(item.transform),
                   item.size,
                   item.colour
               );
            }
        }
    }

    void CLevel::cleanupActors()
    {
        for (auto it {m_actors.rbegin()}; it != m_actors.rend();)
        {
            if (it->get()->flags.isBitSet(CActor::PendingKill))
            {
                if (auto const layer = getLayerFromActor(it->get()))
                    layer->removeActor(it->get());

                it = decltype(it)(m_actors.erase(std::next(it).base()));
            }
            else
                ++it;
        }
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

    const CLevel::LayersMap& CLevel::getLayers() const
    {
        return m_layers;
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

    CLayer* CLevel::getLayerFromActor(const CActor* actor)
    {
        if (const auto it = m_layers.find(actor->getLayer()); it != m_layers.end())
            return &it->second;
        
        return nullptr;
    }
}
