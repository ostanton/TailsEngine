#include <Tails/States/State.hpp>
#include <Tails/Layers/LevelLayer.hpp>
#include <Tails/Layers/ScreenLayer.hpp>
#include <Tails/Subsystems/StateSubsystem.hpp>
#include <Tails/Entities/Entity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    State::State() = default;
    State::~State() = default;

    StateSubsystem& State::getStateSubsystem()
    {
        return *getTypedOuter<StateSubsystem>();
    }

    Engine& State::getEngine()
    {
        return getStateSubsystem().getEngine();
    }

    Layer* State::insertLayer(std::unique_ptr<Layer> layer, size_t index)
    {
        // do better checks and stuff. This could mess up loops
        // in tick and draw if inserted before current item.
        // Somehow defer it till end of frame? Separate vector for insertions?
        // Maybe unordered_map<size_t, std::unique_ptr<Layer>> m_insertingLayers;
        // then in postTick, loop the map and insert into m_layers with the map's
        // key as index and value as value.
        auto it = m_layers.insert(m_layers.begin() + static_cast<long long>(index), std::move(layer));
        // could just return iterator?
        return (*it).get();
    }

    size_t State::addLayer(std::unique_ptr<Layer> layer)
    {
        Debug::print("Adding layer...");
        if (!layer)
        {
            Debug::print("Layer is invalid!");
            return 0;
        }
        layer->outer = this;
        layer->pendingCreate = true;
        layer->init(*this);
        m_layers.push_back(std::move(layer));
        return m_layers.size() - 1;
    }

    Layer* State::getLayer(size_t index)
    {
        // return if index is outside vector's bounds'
        if (index >= m_layers.size())
            return nullptr;

        return m_layers[index].get();
    }

    bool State::removeLayer(size_t index)
    {
        if (index >= m_layers.size())
            return false;

        m_layers[index]->pendingDestroy = true;
        m_layers[index]->removed();
        return true;
    }

    bool State::removeLayer(Layer* layer)
    {
        if (auto it = std::find_if(m_layers.begin(), m_layers.end(),
            [&](auto& uniqueLayer)
            {
                return uniqueLayer.get() == layer;
            }
        ); it != m_layers.end())
        {
            (*it)->pendingDestroy = true;
            (*it)->removed();
            return true;
        }

        return false;
    }

    size_t State::createLevelLayer(const std::string& path)
    {
        size_t index = createLayer<LevelLayer>();
        dynamic_cast<LevelLayer*>(m_layers[index].get())->loadJson(path);
        return index;
    }

    size_t State::createScreenLayer()
    {
        return createLayer<ScreenLayer>();
    }

    void State::init(StateSubsystem& subsystem)
    {

    }

    void State::preTick()
    {
        for (auto& layer : m_layers)
        {
            if (layer->pendingCreate)
            {
                layer->pendingCreate = false;
                layer->added();
            }

            layer->preTick();
        }
    }

    void State::tick(float deltaTime)
    {
        // be weary of insertions while looping here, could be the source of errors TODO
        for (auto& layer : m_layers)
        {
            if (!layer->pendingCreate)
                layer->tick(deltaTime);
        }
    }

    void State::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // be weary here too!
        for (auto& layer : m_layers)
        {
            if (!layer->pendingCreate)
            {
                // somehow combine layer cameras/views into one stored in the state
                // this is then combined into one in the state subsystem that is used
                // in the engine to display the game
                target.draw(*layer, states);
            }
        }
    }

    void State::postTick()
    {
        for (size_t i {0}; i < m_layers.size();)
        {
            m_layers[i]->postTick();

            if (m_layers[i]->pendingDestroy)
                m_layers.erase(m_layers.begin() + static_cast<long long>(i));
            else
                i++;
        }
    }
}
