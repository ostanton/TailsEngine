#include <Tails/String.hpp>

#include <ostream>

namespace tails
{
    CString::CString(const char* str)
        : m_string(str)
    {
    }

    CString& CString::operator=(const char* str)
    {
        m_string = str;
        return *this;
    }

    bool CString::operator==(const char* str) const
    {
        return m_string == str;
    }

    bool CString::operator==(const CString& str) const
    {
        return m_string == str.m_string;
    }

    bool CString::operator!=(const char* str) const
    {
        return m_string != str;
    }

    bool CString::operator!=(const CString& str) const
    {
        return m_string != str.m_string;
    }

    CString CString::operator+(const char* str) const
    {
        return CString {(m_string + str).c_str()};
    }

    CString CString::operator+(const CString& str) const
    {
        return CString {(m_string + str.m_string).c_str()};
    }

    CString& CString::operator+=(const char* str)
    {
        m_string += str;
        return *this;
    }

    CString& CString::operator+=(const CString& str)
    {
        m_string += str.m_string;
        return *this;
    }

    char& CString::operator[](const usize index)
    {
        return m_string[index];
    }

    const char& CString::operator[](const usize index) const
    {
        return m_string[index];
    }

    char* CString::getData()
    {
        return m_string.data();
    }

    const char* CString::getData() const
    {
        return m_string.data();
    }

    std::ostream& operator<<(std::ostream& os, const CString& str)
    {
        os << str.m_string;
        return os;
    }
}
