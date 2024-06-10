#include <Tails/States/State.hpp>
#include <Tails/Layers/LevelLayer.hpp>
#include <Tails/Subsystems/StateSubsystem.hpp>
#include <Tails/Entities/Entity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    State::State()
    {

    }

    State::~State()
    {

    }

    StateSubsystem& State::getStateSubsystem()
    {
        return *getTypedOuter<StateSubsystem>();
    }

    Engine& State::getEngine()
    {
        return getStateSubsystem().getEngine();
    }

    void State::setCameraPosition(const sf::Vector2f& position)
    {
        m_camera.setCenter(position);
    }

    void State::setCameraPosition(float x, float y)
    {
        m_camera.setCenter(x, y);
    }

    void State::setCameraResolution(const sf::Vector2f& resolution)
    {
        m_camera.setSize(resolution);
    }

    void State::setCameraResolution(float w, float h)
    {
        m_camera.setSize(w, h);
    }

    void State::setCamera(const sf::FloatRect& rectangle)
    {
        m_camera.setViewport(rectangle);
    }

    void State::setCamera(const sf::View& camera)
    {
        m_camera = camera;
    }

    Layer* State::insertLayer(std::unique_ptr<Layer> layer, size_t index)
    {
        // do better checks and stuff. This could mess up loops
        // in tick and draw if inserted before current item.
        // Somehow defer it till end of frame? Separate vector for insertions?
        // Maybe unordered_map<size_t, std::unique_ptr<Layer>> m_insertingLayers;
        // then in postTick, loop the map and insert into m_layers with the map's
        // key as index and value as value.
        auto it = m_layers.insert(m_layers.begin() + index, std::move(layer));
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
        layer->pendingCreate = true;
        Debug::print("Layer is pending create, about to initialise...");
        layer->init(*this);
        Debug::print("Layer setup!");
        m_layers.push_back(std::move(layer));
        Debug::print("Layer added!");
        return m_layers.size() - 1;
    }

    Layer* State::getLayer(size_t index)
    {
        // return if index is outside vector's bounds'
        if (index < 0 || index >= m_layers.size())
            return nullptr;

        return m_layers[index].get();
    }

    bool State::removeLayer(size_t index)
    {
        if (index < 0 || index >= m_layers.size())
            return false;

        m_layers[index]->pendingDestroy = true;
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
            return true;
        }

        return false;
    }

    void State::init(StateSubsystem& subsystem)
    {
        createLayer<LevelLayer>();
        Debug::print("Created LevelLayer!");
    }

    void State::preTick()
    {
        for (auto& layer : m_layers)
        {
            layer->preTick();

            if (layer->pendingCreate)
            {
                layer->pendingCreate = false;
                layer->added();
            }
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
            {
                m_layers[i]->removed();
                m_layers.erase(m_layers.begin() + i);
            }
            else
                i++;
        }
    }
}
