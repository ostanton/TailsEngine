#include <Tails/EntryPoint.hpp>
#include <Tails/Application.hpp>

namespace tails
{
    int SEntryPoint::main(const int argc, char* argv[], IApplication& app)
    {
        IApplication::setInstance(app);

        // TODO - abstract into user-friendly arg struct
        if (!app.init(argc, argv))
            return 0;
    
        if (!app.run())
            app.shutdown();
    
        return 0;
    }
}
