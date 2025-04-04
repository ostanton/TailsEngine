#ifdef TAILS_ENABLE_PROFILING
#include <Tails/Profiler.hpp>

#include <SDL3/SDL_timer.h>
#include <iostream>

namespace tails
{
    CScopeProfiler::CScopeProfiler(const char* contextName, const EProfilerCategory category)
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
        std::clog << "Profiling " << categoryStr << " scope \"" << contextName << "\"\n";
    }

    CScopeProfiler::~CScopeProfiler()
    {
        std::clog << "Scope \"" << m_context << "\" finished in "
            << SDL_GetPerformanceCounter() - m_start
            << " milliseconds\n";
    }
}
#endif // TAILS_ENABLE_PROFILING
