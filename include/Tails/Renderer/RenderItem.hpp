#ifndef TAILS_DRAWABLE_HPP
#define TAILS_DRAWABLE_HPP

#include <Tails/Core.hpp>

namespace tails
{
    class IRenderer;
    
    class TAILS_API IRenderItem
    {
        friend IRenderer;
        
    public:
        IRenderItem() = default;
        IRenderItem(const IRenderItem&) = default;
        IRenderItem(IRenderItem&&) noexcept = default;
        IRenderItem& operator=(const IRenderItem&) = default;
        IRenderItem& operator=(IRenderItem&&) noexcept = default;
        virtual ~IRenderItem() = default;

    protected:
        virtual void onRender(IRenderer& renderer) const = 0;
    };
}

#endif // TAILS_DRAWABLE_HPP
