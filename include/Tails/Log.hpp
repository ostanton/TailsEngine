#ifndef TAILS_LOG_HPP
#define TAILS_LOG_HPP

#include <Tails/Core.hpp>

namespace tails
{
    enum class ELogSeverity : u8
    {
        Message,
        Warning,
        Error
    };

    enum class ELogCategory : u8
    {
        Input,
        Profile,
        Render,
        Level,
        Game // Any non-Tails logs
    };
    
    namespace logger
    {
        struct TAILS_API SLogDetails
        {
            const char* fileName;
            u16 line;
        };
        
        TAILS_API void init();
        TAILS_API void log(
            ELogCategory category,
            ELogSeverity severity,
            const char* message,
            const SLogDetails& details
        );
    }
}

#ifdef TAILS_ENABLE_LOGGING
#define TAILS_ENGINE_LOG(CATEGORY, SEVERITY, MSG) \
    ::tails::logger::log( \
        ::tails::ELogCategory::CATEGORY, \
        ::tails::ELogSeverity::SEVERITY, \
        MSG, \
        {TAILS_FILE_NAME, TAILS_LINE} \
    )

#define TAILS_LOG(SEVERITY, MSG) \
    ::tails::logger::log( \
        ::tails::ELogCategory::Game, \
        ::tails::ELogSeverity::SEVERITY, \
        MSG, \
        {TAILS_FILE_NAME, TAILS_LINE} \
    )

#else // TAILS_ENABLE_LOGGING
    #define TAILS_ENGINE_LOG(CATEGORY, SEVERITY, MSG)
    #define TAILS_LOG(SEVERITY, MSG)

#endif // TAILS_ENABLE_LOGGING

#endif // TAILS_LOG_HPP
