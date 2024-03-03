#include <TailsEngine/Core/ApplicationWindow.h>

/**
 * This displays the most bare bones code to use the engine. Default level JSON will be declared in some kind of
 * .ini file or something the engine reads on startup
 */

int main()
{
    const unique_ptr<tails::ApplicationWindow> applicationWindow {
        tails::newObject<tails::ApplicationWindow>(nullptr)
    };

    applicationWindow->mainLoop();

    return 0;
}
