#ifndef TAILS_MULTIEVENT_HPP
#define TAILS_MULTIEVENT_HPP

#include <Tails/Events/Delegate.hpp>

#include <vector>
#include <memory>
#include <algorithm>

namespace tails
{
    template<typename... Args>
    class MultiEvent final
    {
    public:
        MultiEvent() = default;
        explicit MultiEvent(std::unique_ptr<Delegate<Args...>> del)
        {
            m_delegates.emplace_back(std::move(del));
        }
        explicit MultiEvent(std::vector<std::unique_ptr<Delegate<Args...>>>&& delegates)
        {
            m_delegates.reserve(delegates.size());

            for (auto& del : delegates)
            {
                m_delegates.emplace_back(std::move(del));
            }

            delegates.clear();
        }
        MultiEvent(const MultiEvent& other)
        {
            copy(other);
        }

        MultiEvent(MultiEvent&& other) noexcept
        {
            move(std::move(other));
        }

        MultiEvent& operator=(const MultiEvent& other)
        {
            copy(other);
            return *this;
        }

        MultiEvent& operator=(MultiEvent&& other) noexcept
        {
            move(std::move(other));
            return *this;
        }

        MultiEvent& operator+(std::unique_ptr<Delegate<Args...>> del)
        {
            m_delegates.emplace_back(std::move(del));
            return *this;
        }

        MultiEvent& operator+(const MultiEvent& other)
        {
            for (auto& del : other.m_delegates)
            {
                m_delegates.emplace_back(del->clone());
            }

            return *this;
        }

        MultiEvent& operator+(MultiEvent&& other)
        {
            for (auto& del : other.m_delegates)
            {
                m_delegates.emplace_back(std::move(del));
            }

            return *this;
        }

        MultiEvent& operator-(Delegate<Args...>* del)
        {
            if (auto it = std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDel)
                {
                    return *uniqueDel == *del;
                }); it != m_delegates.end())
            {
                m_delegates.erase(it);
            }

            return *this;
        }

        ~MultiEvent() = default;

        /**
         * Adds the specified function
         * @tparam C Object class
         * @param object Object context
         * @param func Class method
         */
        template<typename C>
        void add(C* object, void(C::*function)(Args...))
        {
            m_delegates.emplace_back(std::make_unique<MemberDelegate<C, Args...>>(object, function));
        }

        /**
         * Adds the specified function if it does not already exist
         * @tparam C Object class
         * @param object Object context
         * @param func Class method
         */
        template<typename C>
        bool addUnique(C* object, void(C::*function)(Args...))
        {
            // fail to add if it already exists
            if (auto it = getDelegateIterator(object, function); it != m_delegates.end())
                return false;

            add(object, function);
            return true;
        }

        /**
         * Removes the specified function
         * @tparam C Object class
         * @param object Object context
         * @param func Class method
         * @return Successful
         */
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

        /**
         * Executes every delegate that this MultiEvent owns
         * @param args Function arguments
         */
        void broadcast(Args... args)
        {
            if (m_delegates.empty()) return;

            for (auto& del : m_delegates)
            {
                (*del)(args...);
            }
        }

    private:
        /**
         * Copies another MultiEvent into this one
         * @param other The MultiEvent to copy
         */
        void copy(const MultiEvent& other)
        {
            m_delegates.clear();
            m_delegates.reserve(other.m_delegates.size());

            for (auto& del : other.m_delegates)
            {
                m_delegates.emplace_back(del->clone());
            }
        }

        /**
         * Moves another MultiEvent into this one
         * @param other The MultiEvent to move
         */
        void move(MultiEvent&& other)
        {
            m_delegates.clear();
            m_delegates.reserve(other.m_delegates.size());

            for (auto& del : other.m_delegates)
            {
                m_delegates.emplace_back(std::move(del));
            }

            other.m_delegates.clear();
        }

        template<typename C>
        std::vector<std::unique_ptr<Delegate<Args...>>>::iterator getDelegateIterator(C* object, void(C::*function)(Args...))
        {
            MemberDelegate<C, Args...> del {object, function};
            return std::find_if(m_delegates.begin(), m_delegates.end(),
                [&](auto& uniqueDelegate)
                {
                    return *uniqueDelegate == del;
                });
        }

        std::vector<std::unique_ptr<Delegate<Args...>>> m_delegates;
    };
}

#endif // TAILS_MULTIEVENT_HPP
