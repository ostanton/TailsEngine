#ifndef TAILS_EVENTDELEGATE_HPP
#define TAILS_EVENTDELEGATE_HPP

namespace tails
{
    template<typename... Args>
    struct Delegate
    {
        virtual void execute(Args&&...) = 0;
        virtual void execute(const Args&...) = 0;
    };

    template<typename C, typename... Args>
    struct MemberDelegate : Delegate<Args...>
    {
        MemberDelegate(C* object, void(C::*function)(Args&&...))
            : m_object(object), m_function(function) {}

        void execute(Args&&... args) override
        {
            (m_object->*m_function)(std::forward<Args>(args)...);
        }

        void execute(const Args&... args) override
        {
            (m_object->*m_function)(std::move(args)...);
        }

    private:
        C* m_object;
        void(C::*m_function)(Args&&...);
    };
}

#endif // TAILS_EVENTDELEGATE_HPP
