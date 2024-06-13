#ifndef TAILS_STATE_HPP
#define TAILS_STATE_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Debug.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>

#include <vector>
#include <memory>
#include <string>

namespace tails
{
    class Layer;
    class StateSubsystem;
    class Engine;

    class TAILS_API State : public Object, public sf::Drawable, public Tickable
    {
        friend StateSubsystem;

    public:
        State();
        ~State() override;

        StateSubsystem& getStateSubsystem();
        Engine& getEngine();

        template<typename T>
        size_t createLayer()
        {
            static_assert(std::is_base_of_v<Layer, T>, "Failed to create layer. Template parameter does not derive Layer.");
            Debug::print("Creating layer...");
            return addLayer(std::make_unique<T>());
        }

        template<typename T>
        Layer* insertLayer(size_t index)
        {
            static_assert(std::is_base_of_v<Layer, T>, "Failed to insert layer. Template parameter does not derive Layer.");
            return insertLayer(std::make_unique<T>(), index);
        }

        template<typename T>
        T* getLayer(size_t index)
        {
            static_assert(std::is_base_of_v<Layer, T>, "Failed to get layer. Template parameter does not derive Layer.");
            return static_cast<T*>(getLayer(index));
        }

        Layer* insertLayer(std::unique_ptr<Layer> layer, size_t index);
        size_t addLayer(std::unique_ptr<Layer> layer);
        Layer* getLayer(size_t index);
        bool removeLayer(size_t index);
        bool removeLayer(Layer* layer);

        size_t createLevelLayer(const std::string& path);
        // TODO - accept XML layout files?
        size_t createScreenLayer();

    protected:
        bool tickWhileInactive {false};
        bool drawWhileInactive {false};

        virtual void init(StateSubsystem& subsystem);
        virtual void added() {} // called when added to the stack
        virtual void removed() {} // called when removed from the stack

        virtual void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void postTick() override;

        sf::Vector2f m_customCameraSize {0.f, 0.f};
        std::vector<std::unique_ptr<Layer>> m_layers;
    };
}

#endif // TAILS_STATE_HPP
