#include <TailsEngine/Core/ApplicationWindow.h>

/**
 * Idea - levels will be stored in .json or something similar. Entities will be read within the game from it,
 * creating an array that creates Entity objects. PlayerStart or something similar will be the player start point.
 * Having these entities create on their own is essential, because the idea is to not have to make the developer
 * create their own classes to manually spawn things in code. Obviously things need to spawn in code, for dynamic
 * entities, but you get what I mean.
 *
 * Tiled maps or LDTK or whatever for making the levels. It'll kind of be like Valve's .vmf files, but just for
 * this engine.
 */

int main()
{
    const unique_ptr<tails::ApplicationWindow> applicationWindow {
        tails::newObject<tails::ApplicationWindow>(nullptr)
    };

    applicationWindow->mainLoop();

    return 0;
}
