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
        virtual void execute(Args...) = 0;
        // to avoid slicing, define a clone method
        // TODO - is this necessary??
        virtual Delegate<Args...>* clone() const = 0;

        void operator()(Args... args)
        {
            execute(args...);
        }
    };

    // specialised delegate that holds a free-floating function or functor
    template<typename... Args>
    struct FunctorDelegate : Delegate<Args...>
    {
        explicit FunctorDelegate(void(*inFunctor)(Args...))
            : functor(inFunctor) {}

        void execute(Args... args) override
        {
            (*functor)(args...);
        }

        FunctorDelegate<Args...>* clone() const override
        {
            return new FunctorDelegate<Args...>;
        }

        FunctorDelegate<Args...>& operator=(const FunctorDelegate<Args...>& other)
        {
            if (other != *this)
                functor = other.functor;

            return *this;
        }

        FunctorDelegate<Args...>& operator=(void(*other)(Args...))
        {
            functor = other;
            return *this;
        }

        void(*functor)(Args...);
    };

    // specialised delegate that holds class methods along with their class context as an object
    template<typename C, typename... Args>
    struct MemberDelegate : Delegate<Args...>
    {
        MemberDelegate() = default;

        MemberDelegate(C* inObject, void(C::*inFunction)(Args...))
            : object(inObject), function(inFunction) {}

        void execute(Args... args) override
        {
            (object->*function)(args...);
        }

        MemberDelegate<C, Args...>* clone() const override
        {
            return new MemberDelegate<C, Args...>(object, function);
        }

        MemberDelegate<C, Args...>& operator=(const MemberDelegate<C, Args...>& other)
        {
            if (other != *this)
            {
                object = other.object;
                function = other.function;
            }

            return *this;
        }

        void set(C* inObj, void(C::*inFunc)(Args...))
        {
            object = inObj;
            function = inFunc;
        }

        C* object {nullptr};
        void(C::*function)(Args...) {nullptr};
    };
}

#endif // TAILS_EVENTDELEGATE_HPP
