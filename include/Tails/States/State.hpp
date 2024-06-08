#ifndef TAILS_STATE_HPP
#define TAILS_STATE_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class Layer;
    class StateSubsystem;

    class State : public Object, public sf::Drawable, public Tickable
    {
        friend StateSubsystem;

    public:
        State();
        ~State();

        StateSubsystem& getStateSubsystem();

        void setCameraPosition(const sf::Vector2f& position);
        void setCameraPosition(float x, float y);
        void setCameraResolution(const sf::Vector2f& resolution);
        void setCameraResolution(float w, float h);
        void setCamera(const sf::FloatRect& rectangle);
        void setCamera(const sf::View& camera);
        const sf::View& getCamera() {return m_camera;}

        template<typename T>
        size_t createLayer()
        {
            static_assert(std::is_base_of_v<Layer, T>, "Failed to create layer. Template parameter does not derive Layer.");
            return addLayer(std::make_unique<T>());
        }

        template<typename T>
        Layer* insertLayer(size_t index)
        {
            static_assert(std::is_base_of_v<Layer, T>, "Failed to insert layer. Template parameter does not derive Layer.");
            return insertLayer(std::make_unique<T>(), index);
        }

        Layer* insertLayer(std::unique_ptr<Layer> layer, size_t index);
        size_t addLayer(std::unique_ptr<Layer> layer);
        Layer* getLayer(size_t index);
        bool removeLayer(size_t index);
        bool removeLayer(Layer* layer);

    protected:
        bool tickWhileInactive {false};
        bool drawWhileInactive {true};

        virtual void added() {} // called when added to the stack
        virtual void removed() {} // called when removed from the stack

        virtual void preTick();
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void postTick();

        sf::View m_camera {sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)};
        std::vector<std::unique_ptr<Layer>> m_layers;
    };
}

#endif // TAILS_STATE_HPP
