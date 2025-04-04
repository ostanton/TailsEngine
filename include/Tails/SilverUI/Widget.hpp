#ifndef TAILS_WIDGET_HPP
#define TAILS_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/Renderer/RenderItem.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Templated/Optional.hpp>

namespace tails
{
    class ISlot;
    
    class TAILS_API SWidget : public IRenderItem
    {
        friend ISlot;
        
    public:
        /** This widget's minimum size to be drawn at */
        [[nodiscard]] virtual SVector2f getMinimumSize() const noexcept;

        [[nodiscard]] TOptional<SVector2f> getPosition() const noexcept;

        virtual void onTick(float deltaSeconds);

    protected:
        const ISlot* m_slot {nullptr};
    };
}

#endif // TAILS_WIDGET_HPP
