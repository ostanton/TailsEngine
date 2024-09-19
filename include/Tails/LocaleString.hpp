#ifndef TAILS_LOCALE_STRING_HPP
#define TAILS_LOCALE_STRING_HPP

#include <Tails/Config.hpp>
#include <Tails/Localisation.hpp>

#include <string>
#include <format>

namespace tails
{
    class TAILS_API CLocaleString
    {
    public:
        using Iterator = std::string::iterator;
        using ConstIterator = std::string::const_iterator;
        
        CLocaleString() = default;
        CLocaleString(std::string string) : m_id(-1), m_string(std::move(string)) {}
        CLocaleString(const char* string) : CLocaleString(std::string(string)) {}

        template<typename... ArgsT>
        CLocaleString(int id, ArgsT&&... args)
            :
            m_id(id),
            m_string(std::vformat(CLocalisation::getLocalisedString(id), std::make_format_args(args...))) {}

        CLocaleString(const CLocaleString&) = default;
        CLocaleString(CLocaleString&&) = default;
        CLocaleString& operator=(const CLocaleString&) = default;
        CLocaleString& operator=(CLocaleString&&) = default;

        ~CLocaleString() = default;

        template<typename... ArgsT>
        int setLocaleID(std::string_view id, ArgsT&&... args)
        {
            m_id = CLocalisation::hash(id);
            updateLocale(std::forward<ArgsT>(args)...);
            return m_id;
        }

        template<typename... ArgsT>
        void updateLocale(ArgsT&&... args)
        {
            if (localised())
                m_string = CLocalisation::getLocalisedString(m_id);

            if (sizeof...(args) > 0)
                format(std::forward<ArgsT>(args)...);
        }

        template<typename... ArgsT>
        void format(ArgsT&&... args)
        {
            m_string = std::vformat(m_string, std::make_format_args(args...));
        }

        [[nodiscard]] bool localised() const {return m_id >= 0;}

        [[nodiscard]] const std::string& getString() const {return m_string;}
        [[nodiscard]] int getLocaleID() const {return m_id;}

        template<typename... ArgsT>
        void setString(std::string_view string, ArgsT&&... args)
        {
            if (!localised())
                m_string = std::vformat(string, std::make_format_args(args...));
        }

        CLocaleString& operator=(const std::string& string);
        CLocaleString& operator=(const char* string);

        [[nodiscard]] operator const std::string&() const;

        void setLocalise(bool localise);

        Iterator begin();
        ConstIterator begin() const;
        Iterator end();
        ConstIterator end() const;

        [[nodiscard]] char operator[](size_t index) const;
        [[nodiscard]] size_t getSize() const;
        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] char* getData();
        [[nodiscard]] const char* getData() const;
        
    private:
        int m_id;
        std::string m_string;
    };

    TAILS_API std::ostream& operator<<(std::ostream& stream, const CLocaleString& locString);
}

#define TAILS_LOC_STR(STR_ID, ...) tails::CLocaleString(tails::CLocalisation::hash(#STR_ID), __VA_ARGS__)

#endif // TAILS_LOCALE_STRING_HPP
