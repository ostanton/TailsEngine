#ifndef TAILS_LOG_HPP
#define TAILS_LOG_HPP

#include <Tails/Core.hpp>

namespace tails::logger
{
    enum class ESeverity : u8
    {
        Message,
        Warning,
        Error
    };

    enum class ECategory : u8
    {
        Application,
        LoggerSubsystem,
        AssetSubsystem,
        InputSubsystem,
        AudioSubsystem,
        DebugSubsystem,
        WorldSubsystem,
        WidgetSubsystem,
        ActorRegistry,
        Renderer,
        Game // Any non-Tails engine logs
    };
    
    TAILS_API void init();
    TAILS_API void log(ECategory category, ESeverity severity, const char* fmt, ...);
}

#ifdef TAILS_ENABLE_LOGGING

// TODO - have some TAILS_FMT macro or something so we don't need two different log macros
/**
 * Basic string formatter, used in @code TAILS_LOG@endcode macro
 * @param FMT C-style formatted string
 */
#define TAILS_FMT(FMT, ...) FMT, __VA_ARGS__

/**
 * Logs a string message to the console and a log file
 * @param CATEGORY Logging category, Game if not logging to a specific engine system
 * @param SEVERITY Message, Warning, Error, etc.
 * @param MSG String message
 */
#define TAILS_LOG(CATEGORY, SEVERITY, MSG) \
    ::tails::logger::log( \
        ::tails::logger::ECategory::CATEGORY, \
        ::tails::logger::ESeverity::SEVERITY, \
        MSG \
    )

/**
 * Logs a formatted string to the console and a log file
 * @param CATEGORY Logging category, Game if not logging a specific engine system
 * @param SEVERITY Message, Warning, Error, etc.
 * @param FMT C-style formatted message
 */
#define TAILS_LOG_VA(CATEGORY, SEVERITY, FMT, ...) \
    ::tails::logger::log( \
        ::tails::logger::ECategory::CATEGORY, \
        ::tails::logger::ESeverity::SEVERITY, \
        FMT, \
        __VA_ARGS__ \
    )

#else // TAILS_ENABLE_LOGGING

#define TAILS_FMT(FMT, ...)
#define TAILS_LOG(CATEGORY, SEVERITY, MSG)
#define TAILS_LOG_VA(CATEGORY, SEVERITY, FMT, ...)

#endif // TAILS_ENABLE_LOGGING

#endif // TAILS_LOG_HPP
