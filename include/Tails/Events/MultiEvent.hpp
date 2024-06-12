#ifndef TAILS_MULTIEVENT_HPP
#define TAILS_MULTIEVENT_HPP

#include <Tails/Events/Delegate.hpp>

#include <vector>
#include <memory>
#include <algorithm>

namespace tails
{
    // the same as Event except can hold more than one delegate to broadcast at a time!
    // friends are not allowed with templated classes apparently. Very sad :(
    template<typename... Args>
    class TAILS_API MultiEvent final
    {
    public:
        MultiEvent() = default;
        MultiEvent(const MultiEvent& other)
        {
            // TODO - work out the copy constructor!
        }

        MultiEvent(MultiEvent&& other) noexcept
        {
            // TODO - move because unique_ptr!
            m_delegates = other.m_delegates;
        }

        MultiEvent& operator=(MultiEvent&& other) noexcept
        {
            // same as up there!
            m_delegates = other.m_delegates;
        }

        template<typename C>
        void add(C* object, void(C::*function)(Args&&...))
        {
            m_delegates.push_back(std::make_unique<MemberDelegate<C, Args...>>(object, function));
        }

        template<typename C>
        void add(C* object, void(C::*function)(const Args&...))
        {
            m_delegates.push_back(std::make_unique<MemberDelegate<C, Args...>>(object, function));
        }

        void add(void(*function)(Args&&...))
        {
            m_delegates.push_back(std::make_unique<FunctorDelegate<Args...>>(function));
        }

        void add(void(*function)(const Args&...))
        {
            m_delegates.push_back(std::make_unique<FunctorDelegate<Args...>>(function));
        }

        template<typename C>
        bool addUnique(C* object, void(C::*function)(Args&&...))
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return uniqueDelegate->object == object && uniqueDelegate->function == function;
                }); it != m_delegates.end())
                return false;

            add(object, function);
            return true;
        }

        template<typename C>
        bool addUnique(C* object, void(C::*function)(const Args&...))
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return uniqueDelegate->object == object && uniqueDelegate->function == function;
                }); it != m_delegates.end())
                return false;

            add(object, function);
            return true;
        }

        bool addUnique(void(*function)(Args&&...))
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return uniqueDelegate->functor == function;
                }); it != m_delegates.end())
                return false;

            add(function);
            return true;
        }

        bool addUnique(void(*function)(const Args&...))
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return uniqueDelegate->functor == function;
                }); it != m_delegates.end())
                return false;

            add(function);
            return true;
        }

        template<typename C>
        bool remove(C* object, void(C::*function)(Args&&...))
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return uniqueDelegate->object == object && uniqueDelegate->function == function;
                }); it != m_delegates.end())
            {
                m_delegates.erase(it);
                return true;
            }

            return false;
        }

        template<typename C>
        bool remove(C* object, void(C::*function)(const Args&...))
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return uniqueDelegate->object == object && uniqueDelegate->function == function;
                }); it != m_delegates.end())
            {
                m_delegates.erase(it);
                return true;
            }

            return false;
        }

        bool remove(void(*function)(Args&&...))
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return uniqueDelegate->functor == function;
                }); it != m_delegates.end())
            {
                m_delegates.erase(it);
                return true;
            }

            return false;
        }

        bool remove(void(*function)(const Args&...))
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return uniqueDelegate->functor == function;
                }); it != m_delegates.end())
            {
                m_delegates.erase(it);
                return true;
            }

            return false;
        }

        // unreal engine terminology because it just makes sense
        void broadcast(Args&&... args)
        {
            if (m_delegates.empty()) return;

            for (auto& del : m_delegates)
            {
                del->execute(std::forward<Args>(args)...);
            }
        }

        void broadcast(const Args&... args)
        {
            if (m_delegates.empty()) return;

            for (auto& del : m_delegates)
            {
                del->execute(args...);
            }
        }

    private:
        std::vector<std::unique_ptr<Delegate<Args...>>> m_delegates;
    };
}

#endif // TAILS_MULTIEVENT_HPP
