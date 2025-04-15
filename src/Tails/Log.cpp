#include <Tails/Log.hpp>
#include <Tails/String.hpp>

#include <SDL3/SDL_log.h>

#include <cstdarg>

namespace tails::logger
{
    void init()
    {
        // SDL_Log saves to a file already, so I don't need to do that. Might as well keep this around anyway
        TAILS_LOG(LoggerSubsystem, Message, "Initialised");
    }

    void log(const ECategory category, const ESeverity severity, const char* fmt, ...)
    {
#ifdef TAILS_ENABLE_LOGGING
        CString str;
        switch (category)
        {
        case ECategory::Application:
            str += "Application        ";
            break;
        case ECategory::LoggerSubsystem:
            str += "Logger Subsystem   ";
            break;
        case ECategory::AssetSubsystem:
            str += "Asset Subsystem    ";
            break;
        case ECategory::InputSubsystem:
            str += "Input Subsystem    ";
            break;
        case ECategory::AudioSubsystem:
            str += "Audio Subsystem    ";
            break;
        case ECategory::DebugSubsystem:
            str += "Debug Subsystem    ";
            break;
        case ECategory::WorldSubsystem:
            str += "World Subsystem    ";
            break;
        case ECategory::WidgetSubsystem:
            str += "Widget Subsystem   ";
            break;
        case ECategory::ActorRegistry:
            str += "Actor Registry     ";
            break;
        case ECategory::Renderer:
            str += "Renderer           ";
            break;
        case ECategory::Game:
            str += "Game               ";
            break;
        default:
            str += "Unknown            ";
            break;
        }

        switch (severity)
        {
        case ESeverity::Message:
            str += "Message   ";
            break;
        case ESeverity::Warning:
            str += "Warning   ";
            break;
        case ESeverity::Error:
            str += "Error     ";
            break;
        }

        str += fmt;
        fmt = str.getData();
        
        std::va_list args;
        va_start(args, fmt);
        const int len {SDL_vsnprintf(nullptr, 0, fmt, args)};
        va_end(args);

        auto const msg {static_cast<char*>(SDL_malloc(len + 1))};
        va_start(args, fmt);
        if (SDL_vsnprintf(msg, len + 1, fmt, args) < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_vsnprintf failed!");
            va_end(args);
            return;
        }
        va_end(args);
        
        SDL_Log(msg); // dunno how to make my own log category so this'll have to do!
#endif // TAILS_ENABLE_LOGGING
    }
}
