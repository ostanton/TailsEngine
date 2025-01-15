#include <Tails/UI/SlottedWidget.hpp>
#include <Tails/UI/Widget.hpp>

namespace tails::ui
{
    SSlottedWidget::SSlottedWidget() = default;
    SSlottedWidget::SSlottedWidget(SSlottedWidget&&) noexcept = default;
    SSlottedWidget& SSlottedWidget::operator=(SSlottedWidget&&) noexcept = default;
    SSlottedWidget::~SSlottedWidget() = default;

    CWidget* SSlottedWidget::get() const noexcept
    {
        return content.get();
    }

    CWidget* SSlottedWidget::release() noexcept
    {
        return content.release();
    }

    sf::FloatRect SSlottedWidget::getGlobalBounds() const
    {
        return getTransform().transformRect(content->getLocalBounds());
    }

    CWidget* SSlottedWidget::operator->() const noexcept
    {
        return get();
    }

    SSlottedWidget& SSlottedWidget::operator=(std::unique_ptr<CWidget>&& newContent)
    {
        if (newContent == content)
            return *this;

        content = std::move(newContent);
        return *this;
    }
}
