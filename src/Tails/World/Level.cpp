#include <Tails/World/Level.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/ActorRegistry.hpp>
#include <Tails/World/Layer.hpp>
#include <Tails/World/CameraActor.hpp>
#include <Tails/Renderer/Renderer.hpp>

#include <algorithm>

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

    void CLevel::loadFinished()
    {
        if (!activeCamera)
        {
            activeCamera = spawnActor<CCameraActor>({
                {0.f, 0.f},
                0.f,
                {1.f, 1.f}
            })->cameraComponent;
        }
    }

    void CLevel::initActors() const
    {
        for (const auto& actor : m_actors)
        {
            actor->onInitComponents();
            actor->onSpawn();
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

    void CLevel::destroyActor(const CActor* actor)
    {
        if (const auto it = getActorIterator(actor); it != m_actors.end())
        {
            it->get()->flags.setBit(CActor::PendingKill);
        }
    }

    SVector2f CLevel::worldToScreen(const SVector2f worldPoint) const
    {
        const auto resolution = render::getResolution();

        // Get point relative to camera with zoom
        const auto relative = (worldPoint - camera.position) * camera.zoom;

        // Rotate around camera centre
        const double cosA {std::cos(camera.rotation)};
        const double sinA {std::sin(camera.rotation)};
        const SVector2d rotated = {
            relative.x * cosA - relative.y * sinA,
            relative.x * sinA + relative.y * cosA
        };

        // Move to screen space
        return SVector2f {rotated + resolution / 2.f};
    }

    STransform2D CLevel::worldToScreen(const STransform2D& worldTransform) const
    {
        return {
            .position = worldToScreen(worldTransform.position),
            .rotation = static_cast<float>((worldTransform.rotation - camera.rotation) * (180.f / M_PI)),
            .scale2D = worldTransform.scale2D * camera.zoom,
        };
    }

    SVector2f CLevel::screenToWorld(const SVector2f screenPoint) const
    {
        const auto resolution = render::getResolution();

        // Move origin to camera centre
        const auto relative = screenPoint - resolution / 2.f;

        // Apply inverse rotation
        const double cosA {std::cos(-camera.rotation)};
        const double sinA {std::sin(-camera.rotation)};

        SVector2d unrotated = {
            relative.x * cosA - relative.y * sinA,
            relative.x * sinA + relative.y * cosA
        };

        // Undo zoom
        unrotated /= camera.zoom;

        return SVector2f {unrotated + camera.position};
    }

    STransform2D CLevel::screenToWorld(const STransform2D& screenTransform) const
    {
        return {
            .position = screenToWorld(screenTransform.position),
            .rotation = screenTransform.rotation,
            .scale2D = screenTransform.scale2D / camera.zoom,
        };
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
                render::texture(
                    item.texture,
                    worldToScreen(item.transform),
                    item.size,
                    item.colour
                );
            else
                render::rect(
                    worldToScreen(item.transform),
                    item.size,
                    item.colour
                );
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
