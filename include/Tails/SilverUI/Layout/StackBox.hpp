#ifndef TAILS_STACK_BOX_WIDGET_HPP
#define TAILS_STACK_BOX_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/SilverUI/Panel.hpp>

namespace tails
{
    enum class EHorizontalAlignment : u8
    {
        Left,
        Centre,
        Right,
        Fill
    };

    enum class EVerticalAlignment : u8
    {
        Top,
        Centre,
        Bottom,
        Fill
    };
    
    class TAILS_API SStackBox final : public SPanel
    {
    public:
        class TAILS_API CStackBoxSlot final : public ISlot
        {
        public:
            using ISlot::ISlot;
            
            EHorizontalAlignment hAlign;
            EVerticalAlignment vAlign;

        private:
            void layout() override
            {
                
            }
        };

    private:
        std::unique_ptr<ISlot> makeSlot(std::shared_ptr<SWidget> content) override;
    };
}

#endif // TAILS_STACK_BOX_WIDGET_HPP
