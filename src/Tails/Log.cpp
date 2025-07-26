#include <Tails/Log.hpp>

#ifdef TAILS_ENABLE_LOGGING
#include <Tails/String.hpp>
#include <SDL3/SDL_log.h>
#include <iostream>
#include <fstream>
#endif // TAILS_ENABLE_LOGGING

namespace tails::logger
{
    namespace
    {
        std::ofstream logFileStream;

        bool logToFile(const CString& string)
        {
            if (!logFileStream.is_open())
                return false;

            logFileStream << string << '\n';
            return true;
        }
    }

    void init()
    {
#ifdef TAILS_ENABLE_LOGGING
        // TODO - set up writing to a log file, as SDL_Log isn't used anymore
        logFileStream.open("tails.log");
        if (!logFileStream.is_open())
        {
            TAILS_LOG(LoggerSubsystem, Error, "Failed to create log file");
            return;
        }

        TAILS_LOG(LoggerSubsystem, Message, "Initialised");
#endif // TAILS_ENABLE_LOGGING
    }

    void deinit()
    {
        TAILS_LOG(LoggerSubsystem, Message, "Deinitialised");
        if (logFileStream.is_open())
            logFileStream.close();
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
        case ECategory::Window:
            str += "Window             ";
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
        std::cout << str << '\n';
        logToFile(str);
#endif // TAILS_ENABLE_LOGGING
    }
}
