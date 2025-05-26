#include <Tails/Log.hpp>

#ifdef TAILS_ENABLE_LOGGING
#include <Tails/String.hpp>
#include <Tails/Memory.hpp>
#include <SDL3/SDL_log.h>
#include <cstdarg>
#include <iostream>
#endif // TAILS_ENABLE_LOGGING

namespace tails::logger
{
    void init()
    {
#ifdef TAILS_ENABLE_LOGGING
        // SDL_Log saves to a file already, so I don't need to do that. Might as well keep this around anyway
        TAILS_LOG(LoggerSubsystem, Message, "Initialised");
#endif // TAILS_ENABLE_LOGGING
    }

    void log(const ECategory category, const ESeverity severity, const CString& msg)
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
        case ECategory::Profiler:
            str += "Profiler           ";
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

        str += msg;
        // for now, as zig's clang hates non-literal format strings!
        std::cout << str << '\n';
        //SDL_Log(str.getData()); // dunno how to make my own log category so this'll have to do!
#endif // TAILS_ENABLE_LOGGING
    }
}
