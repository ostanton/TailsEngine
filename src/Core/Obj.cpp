#include <TailsEngine/Core/Obj.h>

#include "TailsEngine/Core/ApplicationWindow.h"
#include "TailsEngine/Debug/Debug.h"

void tails::Object::construct()
{
    
}

void tails::Object::destruct()
{
    
}

tails::ApplicationWindow* tails::Object::getApplicationWindow() const
{
    // Loop through outers until we reach ApplicationWindow
    Object* resultOuter {outer};
    
    while (resultOuter)
    {
        const auto newOuter = dynamic_cast<ApplicationWindow*>(resultOuter);

        if (newOuter)
            return newOuter;

        resultOuter = resultOuter->outer;
    }

    return nullptr;
}

tails::InputManager& tails::Object::getInputManager() const
{
    if (!getApplicationWindow())
        Debug::log("Object::getInputManager - getApplicationWindow returned nullptr");
    return *getApplicationWindow()->m_inputManager;
}

tails::AssetCache& tails::Object::getGlobalAssetCache() const
{
    if (!getApplicationWindow())
        Debug::log("Object::getGlobalAssetCache - getApplicationWindow returned nullptr");
    return getApplicationWindow()->getAssetCache();
}

float tails::Object::getGlobalDeltaTime() const
{
    if (!getApplicationWindow())
        Debug::log("Object::getGlobalDeltaTime - getApplicationWindow returned nullptr");
    return getApplicationWindow()->globalTime.asSeconds();
}
