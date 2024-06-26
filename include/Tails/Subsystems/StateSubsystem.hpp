#ifndef TAILS_STATESUBSYSTEM_HPP
#define TAILS_STATESUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Subsystems/Subsystem.hpp>
#include <Tails/Debug.hpp>

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class State;

    // engine subsystem that manages game states
    // TODO - setup a way for a default state class to be initialised
    class TAILS_API StateSubsystem final : public Subsystem
    {
    public:
        StateSubsystem();
        ~StateSubsystem() override;

        template<typename T>
        T* emplaceState()
        {
            static_assert(std::is_base_of_v<State, T>, "Failed to emplace state, type does not derive State.");
            Debug::print("Emplacing state...");
            m_states.emplace_back(std::make_unique<T>());
            setupState(getActiveState());
            Debug::print("Emplaced state!");
            return static_cast<T*>(getActiveState());
        }

        void pushState(std::unique_ptr<State> state);
        void popState();
        [[nodiscard]] State* getActiveState() const;
        bool isStateActive(State* state) const;

    private:
        void init(Engine& engine) override;
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        void setupState(State* state);

        bool m_popState {false};
        sf::Vector2f m_cameraSize;
        std::vector<std::unique_ptr<State>> m_states;
    };
}

#endif // TAILS_STATESUBSYSTEM_HPP
