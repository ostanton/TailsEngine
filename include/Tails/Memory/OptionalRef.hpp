#ifndef TAILS_OPTIONAL_REF_HPP
#define TAILS_OPTIONAL_REF_HPP

namespace tails
{
    /**
     * "Safe" raw pointer wrapper, serving as a non-owning optional
     * @tparam T Reference type
     */
    template<typename T>
    class TOptionalRef final
    {
    public:
        TOptionalRef() = default;
        TOptionalRef(T& ref)
            : m_ptr(&ref)
        {}
        TOptionalRef(const TOptionalRef&) = default;
        TOptionalRef(TOptionalRef&& other) noexcept
            : m_ptr(other.m_ptr)
        {
            other.m_ptr = nullptr;
        }

        TOptionalRef& operator=(T& ref)
        {
            if (m_ptr == &ref)
                return *this;
            
            m_ptr = &ref;
            return *this;
        }
        
        TOptionalRef& operator=(const TOptionalRef&) = default;
        TOptionalRef& operator=(TOptionalRef&& other) noexcept
        {
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
            return *this;
        }

        ~TOptionalRef() = default;

        [[nodiscard]] bool operator==(const TOptionalRef&) const = default;
        [[nodiscard]] bool operator!=(const TOptionalRef&) const = default;

        [[nodiscard]] explicit operator bool() const {return isValid();}
        [[nodiscard]] bool operator!() const {return !isValid();}

        [[nodiscard]] T& get() {return *m_ptr;}
        [[nodiscard]] const T& get() const {return *m_ptr;}

        [[nodiscard]] T* operator->() {return m_ptr;}
        [[nodiscard]] const T* operator->() const {return m_ptr;}

        [[nodiscard]] bool isValid() const {return m_ptr != nullptr;}
        
    private:
        T* m_ptr {nullptr};
    };
}

#endif // TAILS_OPTIONAL_REF_HPP
