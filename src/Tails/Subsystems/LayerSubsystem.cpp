#include <Tails/Subsystems/LayerSubsystem.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Layers/Layer.hpp>
#include <Tails/States/State.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    LayerSubsystem::LayerSubsystem() = default;
    LayerSubsystem::~LayerSubsystem() = default;

    void LayerSubsystem::preTick()
    {
        if (m_sortLayers)
        {
            // sort layers into new vector
            std::vector<std::unique_ptr<Layer>> sortedLayers;

            for (auto& layer : m_layers)
            {
                sortedLayers.insert(sortedLayers.begin() + layer->m_zOrder, std::move(layer));
            }

            m_layers.clear();
            m_layers.reserve(sortedLayers.size());

            // put layers back into original vector, sorted
            for (auto& layer : sortedLayers)
            {
                m_layers.emplace_back(std::move(layer));
            }

            m_sortLayers = false;
        }

        for (auto& layer : m_layers)
        {
            layer->preTick();

            if (layer->pendingCreate)
            {
                layer->pendingCreate = false;
                layer->postAdd();
            }
        }
    }

    void LayerSubsystem::tick(float deltaTime)
    {
        for (auto& layer : m_layers)
        {
            if (!layer->pendingCreate)
                layer->tick(deltaTime);
        }
    }

    void LayerSubsystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& layer : m_layers)
        {
            if (!layer->pendingCreate)
                target.draw(*layer, states);
        }
    }

    void LayerSubsystem::postTick()
    {
        for (auto it = m_layers.begin(); it != m_layers.end();)
        {
            it->get()->postTick();

            if (it->get()->pendingDestroy)
                m_layers.erase(it);
            else
                ++it;
        }
    }

    Layer* LayerSubsystem::addLayer(std::unique_ptr<Layer> layer, int zOrder)
    {
        if (!layer) return nullptr;

        m_layers.emplace_back(std::move(layer));
        auto back = m_layers.back().get();
        back->outer = this;
        back->m_zOrder = zOrder;
        back->add();
        sortLayers();
        return back;
    }

    void LayerSubsystem::sortLayers()
    {
        m_sortLayers = true;
    }

    void LayerSubsystem::removeLayer(Layer* layer)
    {
        if (!layer) return;

        if (auto it = std::find_if(m_layers.begin(), m_layers.end(),
            [&](auto& uniqueLayer)
            {
                return uniqueLayer.get() == layer;
            }); it == m_layers.end())
            return;

        layer->remove();
        layer->pendingDestroy;
    }

    Layer* LayerSubsystem::getLayerOfZOrder(size_t zOrder)
    {
        for (auto& layer : m_layers)
            if (layer->m_zOrder == zOrder)
                return layer.get();

        return nullptr;
    }
}
