#include <Tails/World/Level.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/ActorRegistry.hpp>
#include <Tails/World/Layer.hpp>

#include <algorithm>

namespace tails
{
    CLevel::CLevel() = default;
    CLevel::~CLevel() = default;

    void CLevel::setActorLayer(CActor* actor, const isize layer)
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

    void CLevel::onTick(const float deltaSeconds)
    {
        for (auto& [id, layer] : m_layers)
        {
            layer.onTick(deltaSeconds);
        }
    }

    void CLevel::onRender(IRenderer& renderer) const
    {
        for (const auto& [id, layer] : m_layers)
        {
            layer.onRender(renderer);
        }
    }

    CActor* CLevel::spawnActor(
        std::unique_ptr<CActor> actor,
        const STransform2D& transform,
        const isize layer
    )
    {
        m_actors.emplace_back(std::move(actor));
        auto& result = *m_actors.back();
        m_layers[layer].m_actors.push_back(&result);
        result.m_layer = layer;
        result.m_owningLevel = this;
        result.onInitComponents();
        result.setTransform(transform);
        result.onSpawn();
        return &result;
    }

    CActor* CLevel::spawnActor(
        const CString& name,
        const STransform2D& transform,
        const isize layer
    )
    {
        return spawnActor(impl::allocateActor(name), transform, layer);
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
