#ifndef TAILS_DELEGATE_HPP
#define TAILS_DELEGATE_HPP

#include <Tails/Core.hpp>
#include <Tails/Delegates/DelegateBase.hpp>

// TODO - make assert not rely on this, in header at least
#include <iostream>
#include <memory>

namespace tails
{
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
        
        template<typename LambdaT>
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

        template<typename T>
        static TDelegate createRaw(T* obj, RawFuncSignature<T> function)
        {
            TDelegate handle;
            handle.bindRaw(obj, function);
            return handle;
        }

        template<typename T>
        static TDelegate createRaw(T* obj, ConstRawFuncSignature<T> function)
        {
            TDelegate handle;
            handle.bindRaw(obj, function);
            return handle;
        }

        template<typename LambdaT>
        void bindLambda(LambdaT&& lambda)
        {
            m_delegate = std::make_unique<TLambdaDelegate<LambdaT, RetT, ArgsT...>>(std::forward<LambdaT>(lambda));
        }

        void bindStatic(StaticFuncSignature function)
        {
            m_delegate = std::make_unique<TStaticDelegate<RetT, ArgsT...>>(function);
        }

        template<typename T>
        void bindRaw(T* obj, RawFuncSignature<T> function)
        {
            m_delegate = std::make_unique<TRawDelegate<false, T, RetT, ArgsT...>>(obj, function);
        }

        template<typename T>
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
