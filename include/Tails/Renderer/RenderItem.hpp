#ifndef TAILS_DRAWABLE_HPP
#define TAILS_DRAWABLE_HPP

#include <Tails/Core.hpp>

namespace tails
{
    class CRenderer;
    
    class TAILS_API IRenderItem
    {
        friend CRenderer;
        
    public:
        IRenderItem() = default;
        IRenderItem(const IRenderItem&) = default;
        IRenderItem(IRenderItem&&) noexcept = default;
        IRenderItem& operator=(const IRenderItem&) = default;
        IRenderItem& operator=(IRenderItem&&) noexcept = default;
        virtual ~IRenderItem() = default;

    protected:
        virtual void onRender(CRenderer& renderer) const = 0;
    };
}

#endif // TAILS_DRAWABLE_HPP
