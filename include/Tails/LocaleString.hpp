#ifndef TAILS_LOCALE_STRING_HPP
#define TAILS_LOCALE_STRING_HPP

#include <Tails/Config.hpp>
#include <Tails/Localisation.hpp>

#include <string>
#include <format>
#include <optional>

namespace tails
{
    class TAILS_API CLocaleString
    {
    public:
        using Iterator = std::string::iterator;
        using ConstIterator = std::string::const_iterator;
        
        CLocaleString() = default;
        CLocaleString(std::string string) : m_string(std::move(string)) {}
        CLocaleString(const char* string) : CLocaleString(std::string(string)) {}

        template<typename... ArgsT>
        CLocaleString(size_t id, ArgsT&&... args)
            :
            m_id(std::make_optional(id)),
            m_string(std::format(CLocalisation::getLocalisedString(id), std::forward<ArgsT>(args)...)) {}

        CLocaleString(const CLocaleString&) = default;
        CLocaleString(CLocaleString&&) = default;
        CLocaleString& operator=(const CLocaleString&) = default;
        CLocaleString& operator=(CLocaleString&&) = default;

        ~CLocaleString() = default;

        template<typename... ArgsT>
        size_t setLocaleID(std::string_view id, ArgsT&&... args)
        {
            m_id = std::make_optional(CLocalisation::hash(id));
            updateLocale(std::forward<ArgsT>(args)...);
            return m_id.value();
        }

        template<typename... ArgsT>
        void updateLocale(ArgsT&&... args)
        {
            if (localised())
                m_string = CLocalisation::getLocalisedString(m_id.value());

            if (sizeof...(args) > 0)
                format(std::forward<ArgsT>(args)...);
        }

        template<typename... ArgsT>
        void format(ArgsT&&... args)
        {
            m_string = std::format(m_string, std::forward<ArgsT>(args)...);
        }

        [[nodiscard]] bool localised() const {return m_id.has_value();}

        [[nodiscard]] const std::string& getString() const {return m_string;}
        [[nodiscard]] std::optional<size_t> getLocaleID() const {return m_id;}

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

        [[nodiscard]] Iterator begin();
        [[nodiscard]] ConstIterator begin() const;
        [[nodiscard]] Iterator end();
        [[nodiscard]] ConstIterator end() const;

        [[nodiscard]] char operator[](size_t index) const;
        [[nodiscard]] size_t getSize() const;
        [[nodiscard]] bool isEmpty() const;
        [[nodiscard]] char* getData();
        [[nodiscard]] const char* getData() const;

        /**
         * Used instead of char& operator[] so we can only allow it if the string is not localised
         * @param index Character position in string
         * @param character New character
         */
        void setCharacter(size_t index, char character);
        
    private:
        std::optional<size_t> m_id {std::nullopt};
        std::string m_string;
    };

    TAILS_API std::ostream& operator<<(std::ostream& stream, const CLocaleString& locString);
}

#define TAILS_LOC_STR(STR_ID, ...) tails::CLocaleString(tails::CLocalisation::hash(#STR_ID), __VA_ARGS__)

#endif // TAILS_LOCALE_STRING_HPP
