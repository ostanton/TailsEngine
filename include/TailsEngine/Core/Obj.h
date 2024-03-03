#pragma once
#include <memory>

namespace tails
{
class AssetCache;
}

namespace tails
{
class ApplicationWindow;
class InputManager;
}

using std::unique_ptr;

namespace tails
{
/**
 * \brief The base class for almost all TailsEngine classes
 * The member initialisation should be as follows:
 * - SFML in constructor
 * - TailsEngine in construct()
 */
class Object
{
public:
    Object() = default;
    virtual ~Object() = default;

    const char* getClassName();

    /**
     * \brief The object this object resides in. Can be null
     */
    Object* outer {nullptr};

    /**
     * \brief Used to initialise TailsEngine-related members, SFML members should be initialised already in the
     * constructor
     */
    virtual void construct();

    virtual void setupData();
    virtual void cleanupData();

    /**
     * \brief Called just before this object's base members are going to be deleted (they are still safe to use)
     * \note This is only called with manual deleteObject(). When an object is deleted from a smart pointer,
     * its normal destructor is used. If you are unsure where to put destruction logic in a non-Entity Object
     * subclass, put it in the destructor
     */
    virtual void destruct();

    ApplicationWindow* getApplicationWindow() const;
    InputManager& getInputManager() const;
    AssetCache& getGlobalAssetCache() const;
    /**
     * \brief Gets the global delta time from ApplicationWindow. This is not the same as the delta time in the
     * GameInstance and Viewport, however should return the same value (or negligibly similar)
     * \return Delta time in seconds
     */
    float getGlobalDeltaTime() const;
};

/**
 * \brief Creates a new object, optionally with an outer
 * \tparam ObjT Object type to create
 * \param outer Object that contains this new object
 * \return Pointer to the created object
 * \note Without an outer, global methods and variables like getGlobalDeltaTime() and various managers
 * cannot be accessed
 */
template<typename ObjT>
ObjT* newObject(Object* outer = nullptr)
{
    static_assert(std::is_base_of_v<Object, ObjT>, "Cannot create non-Object class");
    
    Object* resultObj { new ObjT };

    resultObj->outer = outer;
    resultObj->construct();

    return dynamic_cast<ObjT*>(resultObj);
}

/**
 * \brief Deletes an object pointer. This should only be used on raw pointers, as smart pointers destroy
 * their data automatically
 * \param object Object to delete
 * \return Whether the deletion was successful
 */
inline bool deleteObject(Object* object)
{
    if (object)
    {
        object->destruct();
        delete object;
        return true;
    }

    return false;
}

inline const char* getObjectClassName(Object* object)
{
    return typeid(*object).name();
}

inline bool isObjectValid(const Object* object)
{
    if (!object)
        return false;

    if (!object->outer)
        return false;
    
    return true;
}

}