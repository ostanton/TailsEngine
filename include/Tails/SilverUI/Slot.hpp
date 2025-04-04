#ifndef TAILS_WIDGET_SLOT_HPP
#define TAILS_WIDGET_SLOT_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>

#include <memory>

namespace tails
{
    class SWidget;
    class SPanel;
    
    class TAILS_API ISlot
    {
        friend SPanel;
        
    public:
        explicit ISlot(const SPanel* owner, std::shared_ptr<SWidget> content)
            : m_owner(owner), m_content(std::move(content))
        {
            m_content->m_slot = this;
        }

        ISlot(const ISlot&) = default;
        ISlot(ISlot&&) = default;
        ISlot& operator=(const ISlot&) = default;
        ISlot& operator=(ISlot&&) = default;
        virtual ~ISlot() = default;

        [[nodiscard]] SWidget* getContent() const noexcept {return m_content.get();}
        [[nodiscard]] SVector2f getPosition() const noexcept {return m_position;}

    protected:
        virtual void layout() = 0;

        /** Position of content widget in its panel */
        SVector2f m_position;
        
        const SPanel* m_owner {nullptr};
        std::shared_ptr<SWidget> m_content;
    };
}

#endif // TAILS_WIDGET_SLOT_HPP
