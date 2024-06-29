#ifndef TAILS_EVENTDELEGATE_HPP
#define TAILS_EVENTDELEGATE_HPP

#include <variant>
#include <memory>

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
        Delegate() = default;
        Delegate(const Delegate&) = default;
        Delegate(Delegate&&) = default;
        Delegate& operator=(const Delegate&) = default;
        Delegate& operator=(Delegate&&) = default;
        virtual ~Delegate() = default;

        void operator()(Args... args) {execute(args...);}

        /**
         * Creates a clone of this delegate
         * @return Unique pointer to new delegate memory
         */
        virtual std::unique_ptr<Delegate> clone() const = 0;

        /**
         * Resets the state of this delegate
         */
        virtual void reset() = 0;

    protected:
        virtual void execute(Args...) = 0;
    };

    // specialised delegate that holds class methods along with their class context as an object
    template<typename C, typename... Args>
    struct MemberDelegate : Delegate<Args...>
    {
        MemberDelegate() = default;
        MemberDelegate(const MemberDelegate& other)
            : m_object(other.m_object), m_function(other.m_function) {}
        MemberDelegate(MemberDelegate&& other) noexcept
            : m_object(other.m_object), m_function(other.m_function)
        {
            other.reset();
        }
        MemberDelegate(C* object, void(C::*function)(Args...))
            : m_object(object), m_function(function) {}

        MemberDelegate& operator=(const MemberDelegate& other)
        {
            if (other != *this)
            {
                m_object = other.m_object;
                m_function = other.m_function;
            }
            return *this;
        }

        MemberDelegate& operator=(MemberDelegate&& other) noexcept
        {
            if (other != *this)
            {
                m_object = other.m_object;
                m_function = other.m_function;
                other.reset();
            }
            return *this;
        }

        MemberDelegate& operator=(void(C::*function)(Args...))
        {
            m_function = function;
            return *this;
        }

        bool operator==(const MemberDelegate& other)
        {
            return m_object == other.m_object && m_function == other.m_function;
        }

        bool operator!=(const MemberDelegate& other)
        {
            // CLion says this can be simplified, but then simplifies it to *this != other, which would make an
            // infinite loop, no? funny things
            return !(*this == other);
        }

        ~MemberDelegate() override = default;

        std::unique_ptr<Delegate<Args...>> clone() const override
        {
            return std::make_unique<MemberDelegate>(m_object, m_function);
        }

        void reset() override
        {
            m_object = nullptr;
            m_function = nullptr;
        }

        C* getObject() const {return m_object;}

    private:
        void execute(Args... args) override
        {
            if (m_object && m_function)
                (m_object->*m_function)(args...);
        }

        C* m_object {nullptr};
        void(C::*m_function)(Args...) {nullptr};
    };
}

#endif // TAILS_EVENTDELEGATE_HPP
