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
    };

    // specialised delegate that holds a free-floating function or functor
    template<typename... Args>
    struct FunctorDelegate : Delegate<Args...>
    {
        FunctorDelegate(void(*inFunctor)(Args&&...))
            : functor(inFunctor) {}

        FunctorDelegate(void(*inFunctor)(const Args&...))
            : functor(inFunctor) {}

        void execute(Args&&... args) override
        {
            (*functor)(std::forward<Args>(args)...);
        }

        void execute(const Args&... args) override
        {
            (*functor)(args...);
        }

        FunctorDelegate& operator=(FunctorDelegate& other)
        {
            functor = other.functor;
            return *this;
        }

        std::variant<
            void(*)(Args&&...),
            void(*)(const Args&...)> functor;
    };

    // specialised delegate that holds class methods along with their class context as an object
    template<typename C, typename... Args>
    struct MemberDelegate : Delegate<Args...>
    {
        MemberDelegate(C* inObject, void(C::*inFunction)(Args&&...))
            : object(inObject), function(inFunction) {}

        MemberDelegate(C* inObject, void(C::*inFunction)(const Args&...))
            : object(inObject), function(inFunction) {}

        void execute(Args&&... args) override
        {
            (object->*std::get<void(C::*)(Args&&...)>(function))(std::forward<Args>(args)...);
        }

        void execute(const Args&... args) override
        {
            (object->*std::get<void(C::*)(const Args&...)>(function))(args...);
        }

        MemberDelegate& operator=(MemberDelegate& other)
        {
            object = other.object;
            function = other.function;
            return *this;
        }

        C* object;
        std::variant<
            void(C::*)(Args&&...),
            void(C::*)(const Args&...)> function;
    };
}

#endif // TAILS_EVENTDELEGATE_HPP
