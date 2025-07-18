#ifndef TAILS_DELEGATE_HPP
#define TAILS_DELEGATE_HPP

#include <Tails/Core.hpp>
#include <Tails/Delegates/DelegateBase.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Assert.hpp>

#include <memory>

namespace tails
{
    /**
     * Single-binding delegate which can bind to any function that matches its return type and argument types
     * @tparam RetT Return type
     * @tparam ArgsT Argument types
     */
    template<typename RetT, typename... ArgsT>
    class TDelegate
    {
        template<typename T>
        using RawFuncSignature = typename impl::SMemberFunction<false, T, RetT, ArgsT...>::Signature;
        template<typename T>
        using ConstRawFuncSignature = typename impl::SMemberFunction<true, T, RetT, ArgsT...>::Signature;
        using StaticFuncSignature = RetT(*)(ArgsT...);
        
    public:
        TDelegate() = default;
        TDelegate(const TDelegate& other)
            : m_delegate(other.m_delegate->clone())
        {}
        TDelegate(TDelegate&&) noexcept = default;
        
        TDelegate& operator=(const TDelegate& other)
        {
            if (*this == other)
                return *this;
            
            m_delegate.reset(other.m_delegate->clone());
            return *this;
        }
        
        TDelegate& operator=(TDelegate&&) noexcept = default;
        ~TDelegate() = default;
        
        template<Invocable<RetT, ArgsT...> LambdaT>
        static TDelegate createLambda(LambdaT&& lambda)
        {
            TDelegate handle;
            handle.bindLambda(std::forward<LambdaT>(lambda));
            return handle;
        }

        static TDelegate createStatic(const StaticFuncSignature function)
        {
            TDelegate handle;
            handle.bindStatic(function);
            return handle;
        }

        template<UserType T>
        static TDelegate createRaw(T* obj, RawFuncSignature<T> function)
        {
            TDelegate handle;
            handle.bindRaw(obj, function);
            return handle;
        }

        template<UserType T>
        static TDelegate createRaw(T* obj, ConstRawFuncSignature<T> function)
        {
            TDelegate handle;
            handle.bindRaw(obj, function);
            return handle;
        }

        template<Invocable<RetT, ArgsT...> LambdaT>
        void bindLambda(LambdaT&& lambda)
        {
            m_delegate = std::make_unique<TLambdaDelegate<LambdaT, RetT, ArgsT...>>(std::forward<LambdaT>(lambda));
        }

        void bindStatic(StaticFuncSignature function)
        {
            m_delegate = std::make_unique<TStaticDelegate<RetT, ArgsT...>>(function);
        }

        template<UserType T>
        void bindRaw(T* obj, RawFuncSignature<T> function)
        {
            m_delegate = std::make_unique<TRawDelegate<false, T, RetT, ArgsT...>>(obj, function);
        }

        template<UserType T>
        void bindRaw(T* obj, ConstRawFuncSignature<T> function)
        {
            m_delegate = std::make_unique<TRawDelegate<true, T, RetT, ArgsT...>>(obj, function);
        }

        RetT execute(ArgsT&&... args) const
        {
            TAILS_ASSERT(m_delegate != nullptr, "Failed to execute delegate, it is not bound!");
            return m_delegate->execute(std::forward<ArgsT>(args)...);
        }

        void clear() {m_delegate.reset();}

        [[nodiscard]] bool isBound() const {return m_delegate != nullptr;}

    private:
        std::unique_ptr<IDelegate<RetT, ArgsT...>> m_delegate {nullptr};
    };
}

#define TAILS_DECLARE_DELEGATE(NAME) \
    using NAME = ::tails::TDelegate<void>

#define TAILS_DECLARE_DELEGATE_RET_VAL(NAME, RET_VAL) \
    using NAME = ::tails::TDelegate<RET_VAL>

#define TAILS_DECLARE_DELEGATE_VA_PARAMS(NAME, ...) \
    using NAME = ::tails::TDelegate<void, __VA_ARGS__>

#define TAILS_DECLARE_DELEGATE_RET_VAL_VA_PARAMS(NAME, RET_VAL, ...) \
    using NAME = ::tails::TDelegate<RET_VAL, __VA_ARGS__>

#endif // TAILS_DELEGATE_HPP
