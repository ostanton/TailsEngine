#ifndef TAILS_SLOTTED_WIDGET_HPP
#define TAILS_SLOTTED_WIDGET_HPP

#include <Tails/Config.hpp>

#include <SFML/Graphics/Transformable.hpp>

#include <memory>

namespace tails::ui
{
    class CWidget;
    
    /**
     * Interface for transforming a widget within a slot, allowing only the slot itself to do so.
     * Without being in an SSlottedWidget, a widget cannot have a transform
     */
    struct TAILS_API SSlottedWidget final : sf::Transformable
    {
        SSlottedWidget();
        SSlottedWidget(const SSlottedWidget&) = delete;
        SSlottedWidget(SSlottedWidget&&) noexcept;
        SSlottedWidget& operator=(const SSlottedWidget&) = delete;
        SSlottedWidget& operator=(SSlottedWidget&&) noexcept;
        ~SSlottedWidget() override;
        
        std::unique_ptr<CWidget> content;

        [[nodiscard]] CWidget* get() const noexcept;
        [[nodiscard]] CWidget* release() noexcept;

        [[nodiscard]] sf::FloatRect getGlobalBounds() const;

        CWidget* operator->() const noexcept;
        SSlottedWidget& operator=(std::unique_ptr<CWidget>&& newContent);
    };
}

#endif // TAILS_SLOTTED_WIDGET_HPP
