#ifndef MY_WIDGET_HPP
#define MY_WIDGET_HPP

#include <Tails/UI/CompoundWidget.hpp>
#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/UI/Layout/Canvas.hpp>
#include <Tails/UI/Layout/StackBox.hpp>
#include <Tails/Maths/Colour.hpp>
#include <Tails/UI/Image.hpp>

#include <vector>

class CMyWidget : public tails::ui::CCompoundWidget
{
public:
    CMyWidget()
    {
        using namespace tails::ui;
        auto content = createWidget<CCanvas>(nullptr);
        m_verticalBox = createWidget<CStackBox>(content);
        m_verticalBox->orientation = EOrientation::Vertical;
        setContent(std::move(content));
    }

    void refreshContents(const std::vector<tails::SColour>& items) const
    {
        using namespace tails::ui;
        m_verticalBox->clearChildren();
        for (const auto item : items)
        {
            auto image = createWidget<CImage>(m_verticalBox);
            image->tint = item;
            auto const slot = CStackBox::slotAsStackBoxSlot(image);
            slot->margin.bottom = 8.f;
        }
        CStackBox::slotAsStackBoxSlot(m_verticalBox->getChildren().getChildAt(1))->margin.left = 8.f;
    }

    [[nodiscard]] const std::shared_ptr<tails::ui::CStackBox>& getVerticalBox() const noexcept {return m_verticalBox;}

private:
    std::shared_ptr<tails::ui::CStackBox> m_verticalBox;
};

#endif // MY_WIDGET_HPP
