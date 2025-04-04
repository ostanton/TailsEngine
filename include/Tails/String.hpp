#ifndef TAILS_STRING_HPP
#define TAILS_STRING_HPP

#include <Tails/Core.hpp>

#include <string>

namespace tails
{
    namespace impl
    {
        using CStringImpl = std::string;
    }
    
    /**
     * Dynamic string of characters
     */
    class TAILS_API CString final
    {
    public:
        CString() = default;
        CString(const char* str);
        CString(const CString&) = default;
        CString(CString&&) noexcept = default;

        CString& operator=(const char* str);
        CString& operator=(const CString&) = default;
        CString& operator=(CString&&) noexcept = default;

        bool operator==(const char* str) const;
        bool operator==(const CString& str) const;

        bool operator!=(const char* str) const;
        bool operator!=(const CString& str) const;

        CString operator+(const char* str) const;
        CString operator+(const CString& str) const;

        CString& operator+=(const char* str);
        CString& operator+=(const CString& str);

        char& operator[](usize index);
        const char& operator[](usize index) const;

        friend std::ostream& operator<<(std::ostream& os, const CString& str);

        ~CString() = default;

        [[nodiscard]] char* getData();
        [[nodiscard]] const char* getData() const;

    private:
        impl::CStringImpl m_string;
    };
}

#endif // TAILS_STRING_HPP
