#ifndef TAILS_LAYER_HPP
#define TAILS_LAYER_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <vector>

namespace tails
{
    class State;
    class LayerSubsystem;

    /**
     * A glorified wrapper around a "stack" of states
     */
    class TAILS_API Layer : public Object, public sf::Drawable, public Tickable
    {
        friend LayerSubsystem;

    public:
        [[nodiscard]] LayerSubsystem& getLayerSubsystem() const;

        template<typename T>
        T* pushState()
        {
            static_assert(std::is_base_of_v<State, T>, "Failed to push state, it does not derive State.");
            auto result = std::make_unique<T>();
            result->outer = this;
            result->create();
            return static_cast<T*>(pushState(std::move(result)));
        }

        State* pushState(std::unique_ptr<State> state);

        [[nodiscard]] State* getTopState() const {return m_states.back().get();}
        [[nodiscard]] State* getActiveState() const;
        [[nodiscard]] size_t getActiveStateIndex() const {return m_activeState;}
        [[nodiscard]] State* getState(size_t index) const;
        [[nodiscard]] bool isIndexValid(size_t index) const;

        template<typename T>
        [[nodiscard]] T* getState()
        {
            for (auto& state : m_states)
                if (auto castedState = dynamic_cast<T*>(state.get()))
                    return castedState;

            return nullptr;
        }

        void popState();
        void popState(State* state);
        void popState(size_t index);

        template<typename T>
        void popStateOfType()
        {
            for (auto& state : m_states)
                if (dynamic_cast<T*>(state.get()))
                {
                    popState(state.get());
                    return;
                }
        }

        template<typename T>
        void popAllStatesOfType()
        {
            for (auto& state : m_states)
                if (dynamic_cast<T*>(state.get()))
                    popState(state.get());
        }

        void setZOrder(int zOrder);
        [[nodiscard]] int getZOrder() const {return m_zOrder;}

    protected:
        virtual void add() {}
        virtual void postAdd() {}
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void postTick() override;
        virtual void remove();

    private:
        std::vector<std::unique_ptr<State>> m_states;
        size_t m_activeState;
        int m_zOrder {0};
    };
}

#endif // TAILS_LAYER_HPP
