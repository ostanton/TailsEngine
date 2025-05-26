#include <Tails/Profiler.hpp>

#ifdef TAILS_ENABLE_PROFILING
#include <Tails/Log.hpp>

#include <SDL3/SDL_timer.h>
#endif // TAILS_ENABLE_PROFILING

namespace tails
{
    CScopeProfiler::CScopeProfiler(const char* contextName, const EProfilerCategory category)
#ifdef TAILS_ENABLE_PROFILING
        : m_start(SDL_GetPerformanceCounter()), m_context(contextName)
    {
        const char* categoryStr {};
        switch (category)
        {
        case EProfilerCategory::Engine:
            categoryStr = "ENGINE";
            break;
        case EProfilerCategory::Game:
            categoryStr = "GAME";
            break;
        }
        TAILS_LOG(Profiler, Message, TAILS_FMT("Profiling {} scope '{}'", categoryStr, contextName));
    }
#else // TAILS_ENABLE_PROFILING
    {}
#endif // TAILS_ENABLE_PROFILING

    CScopeProfiler::~CScopeProfiler()
    {
#ifdef TAILS_ENABLE_PROFILING
        TAILS_LOG(Profiler, Message, TAILS_FMT(
            "Scope '{}' finished in {} milliseconds",
            m_context,
            SDL_GetPerformanceCounter() - m_start
        ));
#endif // TAILS_ENABLE_PROFILING
    }
}
