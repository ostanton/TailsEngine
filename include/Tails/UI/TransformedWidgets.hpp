#ifndef TAILS_TRANSFORMED_WIDGETS_HPP
#define TAILS_TRANSFORMED_WIDGETS_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/LayoutData.hpp>

#include <memory>
#include <vector>

namespace tails::ui
{
    class CWidget;

    struct TAILS_API STransformedWidget final
    {
        [[nodiscard]] bool isValid() const noexcept;
        
        std::shared_ptr<CWidget> widget;
        SLayoutData layoutData;
    };

    /**
     * Contains a list of widgets which have been laid out and are ready to be rendered
     */
    class TAILS_API CTransformedWidgets final
    {
    public:
        using Iterator = std::vector<STransformedWidget>::iterator;
        using ConstIterator = std::vector<STransformedWidget>::const_iterator;
        
        void addWidget(STransformedWidget transformedWidget);

        [[nodiscard]] STransformedWidget& operator[](usize index) noexcept;
        [[nodiscard]] const STransformedWidget& operator[](usize index) const noexcept;
        [[nodiscard]] bool validIndex(usize index) const noexcept;
        [[nodiscard]] usize size() const noexcept;

        [[nodiscard]] Iterator begin() noexcept;
        [[nodiscard]] Iterator end() noexcept;
        [[nodiscard]] ConstIterator begin() const noexcept;
        [[nodiscard]] ConstIterator end() const noexcept;

    private:
        std::vector<STransformedWidget> m_widgets;
    };
}

#endif // TAILS_TRANSFORMED_WIDGETS_HPP
