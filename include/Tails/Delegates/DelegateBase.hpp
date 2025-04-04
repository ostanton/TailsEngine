#ifndef TAILS_DELEGATE_BASE_HPP
#define TAILS_DELEGATE_BASE_HPP

#include <type_traits>

namespace tails
{
    /**
     * Delegates implementation based on Simon Coenen's (https://simoncoenen.com/blog/programming/CPP_Delegates).
     * This does not (yet) implement an inline allocator, so is slower (but this engine isn't focused on efficiency
     * anyway). It allocates the function wrapper classes (TLambdaDelegate, TStaticDelegate, etc.)
     * on the heap via an std::unique_ptr, so use with some caution
     */
    template<typename RetT, typename... ArgsT>
    class IDelegate
    {
    public:
        IDelegate() = default;
        IDelegate(const IDelegate&) = default;
        IDelegate(IDelegate&&) noexcept = default;
        IDelegate& operator=(const IDelegate&) = default;
        IDelegate& operator=(IDelegate&&) noexcept = default;
        virtual ~IDelegate() = default;

        virtual RetT execute(ArgsT&&... args) = 0;
        [[nodiscard]] virtual IDelegate* clone() const = 0;
    };

    template<typename LambdaT, typename RetT, typename... ArgsT>
    class TLambdaDelegate final : public IDelegate<RetT, ArgsT...>
    {
    public:
        explicit TLambdaDelegate(LambdaT&& lambda)
            : m_lambda(std::forward<LambdaT>(lambda))
        {}

        RetT execute(ArgsT&&... args) override
        {
            return (m_lambda)(std::forward<ArgsT>(args)...);
        }

        TLambdaDelegate* clone() const override
        {
            return new TLambdaDelegate {*this};
        }

    private:
        LambdaT m_lambda;
    };

    template<typename RetT, typename... ArgsT>
    class TStaticDelegate final : public IDelegate<RetT, ArgsT...>
    {
    public:
        using FuncSignature = RetT(*)(ArgsT...);

        TStaticDelegate(const FuncSignature function)
            : m_function(function)
        {}

        RetT execute(ArgsT&&... args) override
        {
            return m_function(std::forward<ArgsT>(args)...);
        }

        TStaticDelegate* clone() const override
        {
            return new TStaticDelegate {*this};
        }

    private:
        FuncSignature m_function {nullptr};
    };

    namespace impl
    {
        template<bool Const, typename T, typename RetT, typename... ArgsT>
        struct SMemberFunction;

        template<typename T, typename RetT, typename... ArgsT>
        struct SMemberFunction<true, T, RetT, ArgsT...>
        {
            using Signature = RetT(T::*)(ArgsT...) const;
        };

        template<typename T, typename RetT, typename... ArgsT>
        struct SMemberFunction<false, T, RetT, ArgsT...>
        {
            using Signature = RetT(T::*)(ArgsT...);
        };
    }

    template<bool Const, typename T, typename RetT, typename... ArgsT>
    class TRawDelegate final : public IDelegate<RetT, ArgsT...>
    {
    public:
        using FuncSignature = typename impl::SMemberFunction<Const, T, RetT, ArgsT...>::Signature;

        TRawDelegate(T* obj, FuncSignature function)
            : m_obj(obj), m_func(function)
        {}

        RetT execute(ArgsT&&... args) override
        {
            return (m_obj->*m_func)(std::forward<ArgsT>(args)...);
        }

        TRawDelegate* clone() const override
        {
            return new TRawDelegate {*this};
        }

    private:
        T* m_obj {nullptr};
        FuncSignature m_func {nullptr};
    };
}

#endif // TAILS_DELEGATE_BASE_HPP
