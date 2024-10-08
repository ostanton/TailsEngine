#include <Tails/LocaleString.hpp>
#include <Tails/Assert.hpp>

#include <iostream>

namespace tails
{
    CLocaleString& CLocaleString::operator=(const std::string& string)
    {
        setString(string);

        return *this;
    }

    CLocaleString& CLocaleString::operator=(const char* string)
    {
        setString(string);

        return *this;
    }

    CLocaleString::operator const std::string&() const
    {
        return getString();
    }

    void CLocaleString::setLocalise(bool localise)
    {
        if (!localise) m_id = -1;
    }

    CLocaleString::Iterator CLocaleString::begin()
    {
        return m_string.begin();
    }

    CLocaleString::ConstIterator CLocaleString::begin() const
    {
        return m_string.begin();
    }

    CLocaleString::Iterator CLocaleString::end()
    {
        return m_string.end();
    }

    CLocaleString::ConstIterator CLocaleString::end() const
    {
        return m_string.end();
    }

    char CLocaleString::operator[](size_t index) const
    {
        TAILS_ASSERT(index < m_string.size(), "Index to string is out of bounds");
        return m_string[index];
    }

    size_t CLocaleString::getSize() const
    {
        return m_string.size();
    }

    bool CLocaleString::isEmpty() const
    {
        return m_string.empty();
    }

    char* CLocaleString::getData()
    {
        return m_string.data();
    }

    const char* CLocaleString::getData() const
    {
        return m_string.data();
    }

    void CLocaleString::setCharacter(size_t index, char character)
    {
        if (!localised() && index < m_string.size())
            m_string[index] = character;
    }

    std::ostream& operator<<(std::ostream& stream, const CLocaleString& locString)
    {
        stream << locString.getString();
        return stream;
    }
}
