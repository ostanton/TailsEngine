#ifndef TAILS_ENTRY_POINT_HPP
#define TAILS_ENTRY_POINT_HPP

#include <Tails/Core.hpp>

namespace tails
{
    class IApplication;
    
    // call inside main()
    // TODO - completely abstract out main() or similar somehow so platform independence!
    struct TAILS_API SEntryPoint final
    {
        // runtime fails to find this if it's static!
        [[nodiscard]] int main(int argc, char* argv[], IApplication& app);
    };
}

// TODO - is this how we want to tackle main()??
#define TAILS_IMPLEMENT_ENTRY_POINT(APP_CLASS, APP_NAME) \
    namespace tails {SAppCreateData gAppCreateData {APP_NAME};} \
    int main(const int argc, char* argv[]) \
    { \
        APP_CLASS app; \
        return ::tails::SEntryPoint{}.main(argc, argv, app); \
    }

#endif // TAILS_ENTRY_POINT_HPP
