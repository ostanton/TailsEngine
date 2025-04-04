#ifndef TAILS_PROFILER_HPP
#define TAILS_PROFILER_HPP

#ifdef TAILS_ENABLE_PROFILING
#include <Tails/Core.hpp>

namespace tails
{
    enum class EProfilerCategory : u8
    {
        Engine,
        Game
    };
    
    class TAILS_API CScopeProfiler final
    {
    public:
        CScopeProfiler() = delete;
        explicit CScopeProfiler(const char* contextName, EProfilerCategory category);
        CScopeProfiler(const CScopeProfiler&) = delete;
        CScopeProfiler(CScopeProfiler&&) = delete;
        CScopeProfiler& operator=(const CScopeProfiler&) = delete;
        CScopeProfiler& operator=(CScopeProfiler&&) = delete;
        ~CScopeProfiler();

    private:
        u64 m_start;
        const char* m_context;
    };
}

#define TAILS_PROFILE_SCOPE(NAME, CATEGORY) \
    ::tails::CScopeProfiler {NAME, ::tails::EProfilerCategory::CATEGORY}
#define TAILS_PROFILE_FUNCTION() TAILS_PROFILE_SCOPE(TAILS_FUNCTION_NAME, Game)
#define TAILS_PROFILE_ENGINE_FUNCTION() TAILS_PROFILE_SCOPE(TAILS_FUNCTION_NAME, Engine)

#else // TAILS_ENABLE_PROFILING
    #define TAILS_PROFILE_SCOPE(NAME, CATEGORY)
    #define TAILS_PROFILE_FUNCTION()
    #define TAILS_PROFILE_ENGINE_FUNCTION()

#endif // TAILS_ENABLE_PROFILING

#endif // TAILS_PROFILER_HPP
