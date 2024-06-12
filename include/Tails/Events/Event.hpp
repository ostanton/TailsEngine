#ifndef TAILS_EVENT_HPP
#define TAILS_EVENT_HPP

#include <Tails/Events/Delegate.hpp>

#include <memory>

namespace tails
{
    template<typename... Args>
    class TAILS_API Event final
    {
    public:
        // TODO -  fix these so we can only move events and not copy them
        Event() = default;
        Event(const Event& other)
        {
            //m_delegate = std::make_unique<Delegate<Args...>>(other.m_delegate);
        }
        Event(Event&& other) noexcept
        {
            m_delegate = std::move(other.m_delegate);
        }
        Event& operator=(const Event& other)
        {
            //m_delegate = std::make_unique<Delegate<Args...>>(other.m_delegate);
            return *this;
        }
        Event& operator=(Event&& other) noexcept
        {
            m_delegate = std::move(other.m_delegate);
            return *this;
        }
        ~Event() = default;

        // binds create the delegate wrapper. users do not interface with the delegate class when using events
        template<typename C>
        void bind(C* object, void(C::*function)(Args&&...))
        {
            m_delegate = std::make_unique<MemberDelegate<C, Args...>>(object, function);
        }

        template<typename C>
        void bind(C* object, void(C::*function)(const Args&...))
        {
            m_delegate = std::make_unique<MemberDelegate<C, Args...>>(object, function);
        }

        void bind(void(*function)(Args&&...))
        {
            m_delegate = std::make_unique<FunctorDelegate<Args...>>(function);
        }

        void bind(void(*function)(const Args&...))
        {
            m_delegate = std::make_unique<FunctorDelegate<Args...>>(function);
        }

        void unbind() {m_delegate.reset();}

        void execute(Args&&... args)
        {
            if (!m_delegate) return;

            m_delegate->execute(std::forward<Args>(args)...);
        }

        void execute(const Args&... args)
        {
            if (!m_delegate) return;

            m_delegate->execute(args...);
        }

    private:
        std::unique_ptr<Delegate<Args...>> m_delegate;
    };
}

#endif // TAILS_EVENT_HPP
