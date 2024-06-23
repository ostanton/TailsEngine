#ifndef TAILS_MULTIEVENT_HPP
#define TAILS_MULTIEVENT_HPP

#include <Tails/Events/Delegate.hpp>

#include <vector>
#include <memory>
#include <algorithm>

namespace tails
{
    // the same as Event except can hold more than one delegate to broadcast at a time!
    // friends are not allowed with templated classes, apparently. Very sad :(
    template<typename... Args>
    class MultiEvent final
    {
    public:
        MultiEvent() = default;
        MultiEvent(const MultiEvent&) noexcept = default;
        MultiEvent& operator=(const MultiEvent&) noexcept = default;

        MultiEvent(MultiEvent&& other) noexcept
        {
            m_delegates.reserve(other.m_delegates.size());
            size_t otherSize {other.m_delegates.size()};
            for (auto& del : other.m_delegates)
            {
                m_delegates.push_back(del);
            }
        }

        MultiEvent& operator=(MultiEvent&& other) noexcept
        {
            m_delegates.reserve(other.m_delegates.size());
            size_t otherSize {other.m_delegates.size()};
            for (auto& del : other.m_delegates)
            {
                m_delegates.push_back(del);
            }

            return *this;
        }

        template<typename C>
        void add(C* object, void(C::*function)(Args...))
        {
            m_delegates.emplace_back(
                std::make_shared<MemberDelegate<C, Args...>>(object, function)
            );
        }

        void add(void(*function)(Args...))
        {
            m_delegates.emplace_back(
                std::make_shared<FunctorDelegate<Args...>>(function)
            );
        }

        template<typename C>
        bool addUnique(C* object, void(C::*function)(Args...))
        {
            if (auto it = getDelegateIterator(object, function); it != m_delegates.end())
                return false;

            add(object, function);
            return true;
        }

        bool addUnique(void(*function)(Args...))
        {
            if (auto it = getDelegateIterator(function); it != m_delegates.end())
                return false;

            add(function);
            return true;
        }

        template<typename C>
        bool remove(C* object, void(C::*function)(Args...))
        {
            if (auto it = getDelegateIterator(object, function); it != m_delegates.end())
            {
                m_delegates.erase(it);
                return true;
            }

            return false;
        }

        bool remove(void(*function)(Args...))
        {
            if (auto it = getDelegateIterator(function); it != m_delegates.end())
            {
                m_delegates.erase(it);
                return true;
            }

            return false;
        }

        // unreal engine terminology because it just makes sense
        void broadcast(Args... args)
        {
            if (m_delegates.empty()) return;

            for (auto& del : m_delegates)
            {
                del->execute(args...);
            }
        }

    private:
        template<typename C>
        std::vector<std::unique_ptr<Delegate<Args...>>>::iterator getDelegateIterator(C* object, void(C::*function)(Args...))
        {
            return std::find_if(m_delegates.begin(), m_delegates.end(),
            [&](auto& uniqueDelegate)
            {
                return uniqueDelegate->object == object && uniqueDelegate->function == function;
            });
        }

        std::vector<std::unique_ptr<Delegate<Args...>>>::iterator getDelegateIterator(void(*function)(Args...))
        {
            return std::find_if(m_delegates.begin(), m_delegates.end(),
            [&](auto& uniqueDelegate)
            {
                return uniqueDelegate->functor == function;
            });
        }

        // vector of pairs, delegates and their type (as casting is not an option)
        std::vector<std::shared_ptr<Delegate<Args...>>> m_delegates;
    };
}

#endif // TAILS_MULTIEVENT_HPP
