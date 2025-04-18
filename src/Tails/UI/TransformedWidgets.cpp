#include <Tails/UI/TransformedWidgets.hpp>

namespace tails::ui
{
    bool STransformedWidget::isValid() const noexcept
    {
        return widget != nullptr;
    }

    void CTransformedWidgets::addWidget(STransformedWidget transformedWidget)
    {
        m_widgets.emplace_back(std::move(transformedWidget));
    }

    STransformedWidget& CTransformedWidgets::operator[](const usize index) noexcept
    {
        return m_widgets[index];
    }

    const STransformedWidget& CTransformedWidgets::operator[](const usize index) const noexcept
    {
        return m_widgets[index];
    }

    bool CTransformedWidgets::validIndex(const usize index) const noexcept
    {
        return index < m_widgets.size();
    }

    usize CTransformedWidgets::size() const noexcept
    {
        return m_widgets.size();
    }

    CTransformedWidgets::Iterator CTransformedWidgets::begin() noexcept
    {
        return m_widgets.begin();
    }

    CTransformedWidgets::Iterator CTransformedWidgets::end() noexcept
    {
        return m_widgets.end();
    }

    CTransformedWidgets::ConstIterator CTransformedWidgets::begin() const noexcept
    {
        return m_widgets.begin();
    }

    CTransformedWidgets::ConstIterator CTransformedWidgets::end() const noexcept
    {
        return m_widgets.end();
    }
}
