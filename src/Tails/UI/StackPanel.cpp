#include <Tails/UI/StackPanel.hpp>
#include <Tails/UI/StackPanelSlot.hpp>

namespace tails::ui
{
    CStackPanel::CStackPanel() = default;
    CStackPanel::CStackPanel(CStackPanel&&) noexcept = default;
    CStackPanel& CStackPanel::operator=(CStackPanel&&) noexcept = default;
    CStackPanel::~CStackPanel() = default;
}
