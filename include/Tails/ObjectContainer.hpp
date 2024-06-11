#ifndef TAILS_OBJECTCONTAINER_HPP
#define TAILS_OBJECTCONTAINER_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <vector>
#include <memory>

namespace tails
{
    // somehow support maps too??
    // currently only supports object types
    // the idea behind this is to provide a simple interface for automatically ticking, etc.
    // its objects so I don't have to keep repeating the same functionality between different classes.
    // Object class would have an init method or something, then a create for the deferred stuff?
    template<typename T>
    class ObjectContainer : public Object, public Tickable
    {
        static_assert(std::is_base_of_v<Object, T>, "Type in ObjectContainer must derive Object.");

    protected:
        std::vector<std::unique_ptr<T>> m_objects;
    };
}

#endif // TAILS_OBJECTCONTAINER_HPP
