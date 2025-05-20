#include <Tails/Profiler.hpp>

#ifdef TAILS_ENABLE_PROFILING
#include <SDL3/SDL_timer.h>
#include <iostream>
#endif // TAILS_ENABLE_PROFILING

namespace tails
{
    CScopeProfiler::CScopeProfiler(const char* contextName, const EProfilerCategory category)
        : m_start(SDL_GetPerformanceCounter()), m_context(contextName)
    {
#ifdef TAILS_ENABLE_PROFILING
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
        std::clog << "Profiling " << categoryStr << " scope \"" << contextName << "\"\n";
#endif // TAILS_ENABLE_PROFILING
    }

    CScopeProfiler::~CScopeProfiler()
    {
#ifdef TAILS_ENABLE_PROFILING
        std::clog << "Scope \"" << m_context << "\" finished in "
            << SDL_GetPerformanceCounter() - m_start
            << " milliseconds\n";
#endif // TAILS_ENABLE_PROFILING
    }
}
