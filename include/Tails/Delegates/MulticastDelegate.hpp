#ifndef TAILS_MULTICAST_DELEGATE_HPP
#define TAILS_MULTICAST_DELEGATE_HPP

#include <Tails/Core.hpp>
#include <Tails/Delegates/Delegate.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Assert.hpp>

#include <vector>

namespace tails
{
    template<typename... ArgsT>
    class TMulticastDelegate
    {
        template<typename T>
        using RawFuncSignature = typename impl::SMemberFunction<false, T, void, ArgsT...>::Signature;
        template<typename T>
        using ConstRawFuncSignature = typename impl::SMemberFunction<true, T, void, ArgsT...>::Signature;
        using StaticFuncSignature = void(*)(ArgsT...);

    public:
        using Delegate = TDelegate<void, ArgsT...>;
        using DelegateHandle = usize;
        
        TMulticastDelegate() = default;
        TMulticastDelegate(const TMulticastDelegate& other) {clone(other);}
        TMulticastDelegate(TMulticastDelegate&&) noexcept = default;
        explicit TMulticastDelegate(Delegate&& del)
        {
            m_delegates.emplace_back(std::move(del));
        }

        TMulticastDelegate& operator=(const TMulticastDelegate& other)
        {
            if (*this != other)
                clone(other);
            
            return *this;
        }
        TMulticastDelegate& operator=(TMulticastDelegate&&) noexcept = default;
        ~TMulticastDelegate() = default;

        DelegateHandle add(Delegate&& delegate)
        {
            // TODO - try not to reallocate stuff if possible. Can do later when optimising
            m_delegates.emplace_back(std::move(delegate));
            return m_delegates.size() - 1;
        }

        template<Invocable<void, ArgsT...> LambdaT>
        DelegateHandle addLambda(LambdaT&& lambda)
        {
            return add(Delegate::createLambda(std::forward<LambdaT>(lambda)));
        }

        DelegateHandle addStatic(const StaticFuncSignature function)
        {
            return add(Delegate::createStatic(function));
        }

        template<UserType T>
        DelegateHandle addRaw(T* obj, RawFuncSignature<T> function)
        {
            return add(Delegate::createRaw(obj, function));
        }

        template<UserType T>
        DelegateHandle addRaw(T* obj, ConstRawFuncSignature<T> function)
        {
            return add(Delegate::createRaw(obj, function));
        }

        bool remove(const DelegateHandle handle)
        {
            if (isLocked())
                return false;

            lock();
            for (auto i {0}; i < m_delegates.size();)
            {
                if (handle == i)
                {
                    m_delegates.erase(m_delegates.begin() + i);
                    unlock();
                    return true;
                }
            }
            unlock();
            return false;
        }

        [[nodiscard]] bool isBound() const {return !m_delegates.isEmpty();}
        [[nodiscard]] bool isBound(const DelegateHandle handle) const {return handle < m_delegates.size();}

        void removeAll()
        {
            if (isLocked())
                return;

            m_delegates.clear();
        }

        void broadcast(ArgsT&&... args)
        {
            lock();
            for (const Delegate& del : m_delegates)
            {
                del.execute(std::forward<ArgsT>(args)...);
            }
            unlock();
        }

    private:
        void clone(const TMulticastDelegate& other)
        {
            if (!m_delegates.empty())
                m_delegates.clear();
            
            m_delegates.reserve(other.m_delegates.size());
            for (const auto& del : other.m_delegates)
            {
                m_delegates.emplace_back(del);
            }
        }

        void lock() {m_lockCount++;}
        void unlock()
        {
            TAILS_ASSERT(m_lockCount > 0, "TMulticastDelegate lock count is less than 0, somewhere failed to unlock!");
            m_lockCount--;
        }
        [[nodiscard]] bool isLocked() const {return m_lockCount > 0;}

        /** If > 0, disallow removal of delegates because we are iterating them */
        usize m_lockCount {0};
        std::vector<Delegate> m_delegates;
    };
}

#define TAILS_DECLARE_MULTICAST_DELEGATE(NAME) \
    using NAME = ::tails::TMulticastDelegate<>

#define TAILS_DECLARE_MULTICAST_DELEGATE_VA_PARAMS(NAME, ...) \
    using NAME = ::tails::TMulticastDelegate<__VA_ARGS__>

#endif // TAILS_MULTICAST_DELEGATE_HPP
