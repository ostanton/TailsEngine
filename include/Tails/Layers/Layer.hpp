#ifndef TAILS_LAYER_HPP
#define TAILS_LAYER_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Layers/LayerCamera.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
    class State;
    class Engine;

    class TAILS_API Layer : public Object, public sf::Drawable, public Tickable
    {
        friend State;

    public:
        inline LayerCamera& getCamera() {return m_camera;}

    protected:
        virtual void init(State& state) {}
        virtual void added() {}
        virtual void removed() {}

        State& getState();
        Engine& getEngine();

    private:
        LayerCamera m_camera;
    };
}

#endif // TAILS_LAYER_HPP
