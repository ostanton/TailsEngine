#ifndef TAILS_LOG_HPP
#define TAILS_LOG_HPP

#include <Tails/Core.hpp>

namespace tails
{
    namespace logger
    {
        struct TAILS_API SDetails
        {
            const char* fileName;
            u16 line;
        };

        enum class ESeverity : u8
        {
            Message,
            Warning,
            Error
        };

        enum class ECategory : u8
        {
            Input,
            Profile,
            Render,
            Level,
            Game // Any non-Tails logs
        };
        
        TAILS_API void init();
        TAILS_API void log(
            ECategory category,
            ESeverity severity,
            const char* message,
            const SDetails& details
        );
    }
}

#ifdef TAILS_ENABLE_LOGGING
#define TAILS_ENGINE_LOG(CATEGORY, SEVERITY, MSG) \
    ::tails::logger::log( \
        ::tails::logger::ECategory::CATEGORY, \
        ::tails::logger::ESeverity::SEVERITY, \
        MSG, \
        {TAILS_FILE_NAME, TAILS_LINE} \
    )

#define TAILS_LOG(SEVERITY, MSG) \
    ::tails::logger::log( \
        ::tails::logger::ECategory::Game, \
        ::tails::logger::ESeverity::SEVERITY, \
        MSG, \
        {TAILS_FILE_NAME, TAILS_LINE} \
    )

#else // TAILS_ENABLE_LOGGING
    #define TAILS_ENGINE_LOG(CATEGORY, SEVERITY, MSG)
    #define TAILS_LOG(SEVERITY, MSG)

#endif // TAILS_ENABLE_LOGGING

#endif // TAILS_LOG_HPP
