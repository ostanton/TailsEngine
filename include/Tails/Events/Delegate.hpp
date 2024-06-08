#ifndef TAILS_EVENTDELEGATE_HPP
#define TAILS_EVENTDELEGATE_HPP

#include <variant>

namespace tails
{
    /*
     * A delegate is a wrapper for any kind of function. It has
     * specialised children for member functions, etc. and acts
     * similarly to std::function and any other functor, where
     * it overrides the operator() to act like a normal function
     */
    template<typename... Args>
    struct Delegate
    {
        virtual void execute(Args&&...) = 0;
        virtual void execute(const Args&...) = 0;

        void operator()(Args&&... args)
        {
            execute(std::forward<Args>(args)...);
        }

        void operator()(const Args&... args)
        {
            execute(args...);
        }

        virtual Delegate& operator=(Delegate&) = 0;
    };

    // specialised delegate that holds a free-floating function or functor
    template<typename... Args>
    struct FunctorDelegate : Delegate<Args...>
    {
        friend class MultiEvent;

        FunctorDelegate(void(*functor)(Args&&...))
            : m_functor(functor) {}

        FunctorDelegate(void(*functor)(const Args&...))
            : m_functor(functor) {}

        void execute(Args&&... args) override
        {
            (*m_functor)(std::forward<Args>(args)...);
        }

        void execute(const Args&... args) override
        {
            (*m_functor)(args...);
        }

        FunctorDelegate& operator=(FunctorDelegate& other) override
        {
            m_functor = other.m_functor;
            return *this;
        }

    private:
        std::variant<
            void(*)(Args&&...),
            void(*)(const Args&...)> m_functor;
    };

    // specialised delegate that holds class methods along with their class context as an object
    template<typename C, typename... Args>
    struct MemberDelegate : Delegate<Args...>
    {
        friend class MultiEvent;

        MemberDelegate(C* object, void(C::*function)(Args&&...))
            : m_object(object), m_function(function) {}

        MemberDelegate(C* object, void(C::*function)(const Args&...))
            : m_object(object), m_function(function) {}

        void execute(Args&&... args) override
        {
            (m_object->*std::get<void(C::*)(Args&&...)>(m_function))(std::forward<Args>(args)...);
        }

        void execute(const Args&... args) override
        {
            (m_object->*std::get<void(C::*)(const Args&...)>(m_function))(args...);
        }

        MemberDelegate& operator=(MemberDelegate& other) override
        {
            m_object = other.m_object;
            m_function = other.m_function;
            return *this;
        }

    private:
        C* m_object;
        std::variant<
            void(C::*)(Args&&...),
            void(C::*)(const Args&...)> m_function;
    };
}

#endif // TAILS_EVENTDELEGATE_HPP
