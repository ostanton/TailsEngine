#pragma once

#include "Obj.h"

namespace tails
{
class Entity;
}

namespace tails
{
/**
 * \brief Base class for all Entity Components. These do not draw nor have a transform by default,
 * use PrimitiveComponent for that
 */
class Component : public Object
{
    friend Entity;
    
protected:
    virtual void create() {}
    virtual void update(float deltaTime) {}
    virtual void destroy() {}
};

}
