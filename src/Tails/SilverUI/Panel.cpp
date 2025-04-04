#include <Tails/SilverUI/Panel.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails
{
    SPanel::~SPanel() = default;

    ISlot* SPanel::addChild(std::shared_ptr<SWidget> content)
    {
        m_slots.emplace_back(makeSlot(std::move(content)));
        return m_slots.back().get();
    }

    void SPanel::onTick(const float deltaSeconds)
    {
        SWidget::onTick(deltaSeconds);

        for (const auto& slot : m_slots)
        {
            slot->m_content->onTick(deltaSeconds);
        }
    }

    void SPanel::onRender(IRenderer& renderer) const
    {
        for (const auto& slot : m_slots)
        {
            renderer.render(*slot->m_content);
        }
    }
}
