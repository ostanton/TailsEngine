#include <Tails/Log.hpp>

#ifdef TAILS_ENABLE_LOGGING
#include <Tails/String.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#endif // TAILS_ENABLE_LOGGING

namespace tails::logger
{
    namespace
    {
        std::ofstream gLogFileStream;
        bool gInitialised {false};

        std::stringstream& getLogStringStream()
        {
            static std::stringstream stream;
            return stream;
        }

        bool logToFile()
        {
            if (!gLogFileStream.is_open() || !gInitialised)
                return false;

            gLogFileStream << getLogStringStream().rdbuf();
            getLogStringStream().clear();
            return true;
        }
    }

    void init()
    {
#ifdef TAILS_ENABLE_LOGGING
        gLogFileStream.open("tails.log");
        if (!gLogFileStream.is_open())
        {
            TAILS_LOG(LoggerSubsystem, Error, "Failed to create log file");
            return;
        }

        gInitialised = true;
        TAILS_LOG(LoggerSubsystem, Message, "Initialised");
#endif // TAILS_ENABLE_LOGGING
    }

    void deinit()
    {
#ifdef TAILS_ENABLE_LOGGING
        TAILS_LOG(LoggerSubsystem, Message, "Deinitialised");
        if (gLogFileStream.is_open())
            gLogFileStream.close();
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
        getLogStringStream() << str << '\n';
        // TODO - only send to file under certain conditions?
        logToFile();
#endif // TAILS_ENABLE_LOGGING
    }
}
