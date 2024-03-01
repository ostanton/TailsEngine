#pragma once
#include <memory>

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

    /**
     * \brief The object this object resides in. Can be null
     */
    Object* outer {nullptr};

    /**
     * \brief Used to initialise TailsEngine-related members, SFML members should be initialised already in the
     * constructor
     */
    virtual void construct();

    /**
     * \brief Called just before this object's base members are going to be deleted (they are still safe to use)
     */
    virtual void destruct();
};

template<typename ObjT>
ObjT* newObject(Object* outer = nullptr)
{
    Object* resultObj { new ObjT };

    resultObj->outer = outer;
    resultObj->construct();

    return dynamic_cast<ObjT*>(resultObj);
}

}