#ifndef TAILS_STATESTACK_HPP
#define TAILS_STATESTACK_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include <memory>
#include <vector>

namespace tails
{
    class State;
    class Engine;

    class StateStack final : public Object, public sf::Drawable, public Tickable
    {
        using StatePtr = std::unique_ptr<State>;
        friend class Engine;

    public:
        StateStack();
        ~StateStack();

        template<typename T, typename... ArgsT>
        T* emplaceState(ArgsT&&... args)
        {
            m_states.push_back(std::make_unique<T>(std::forward<ArgsT>(args)...));
            addState(activeState());
            return static_cast<T*>(activeState());
        }

        void pushState(std::unique_ptr<State> state);

        void popState();
        State* activeState() const;
        bool isStateActive(State* state) const;
        std::vector<StatePtr>& getVector();

        Engine& getEngine();

    private:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        void initState(State* state); // DOES NOT CALL create() OR added() METHODS. PURELY FOR SETTING MEMBERS
        void addState(State* state); // merely calls "added()" on the target state

        void removeStates();

        sf::Vector2f m_defaultCameraRes;
        std::vector<StatePtr> m_states;
    };
}

#endif // TAILS_STATESTACK_HPP
