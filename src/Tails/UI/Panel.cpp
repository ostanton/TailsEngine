#include <Tails/UI/Panel.hpp>
#include <Tails/UI/Slot.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <algorithm>

namespace tails::ui
{
    CPanel::CPanel() = default;
    CPanel::CPanel(CPanel&&) noexcept = default;
    CPanel& CPanel::operator=(CPanel&&) noexcept = default;
    CPanel::~CPanel() = default;

    CWidget* CPanel::getChildAt(const size_t index) const
    {
        if (!isIndexValid(index)) return nullptr;

        return m_slots[index]->getContent();
    }

    std::optional<size_t> CPanel::getChildIndex(const CWidget* child) const
    {
        if (const auto it = getSlotIterator(child); it != m_slots.end())
            return std::make_optional(it - m_slots.begin());

        return std::nullopt;
    }

    std::unique_ptr<CWidget> CPanel::releaseChild(const size_t index) const
    {
        if (!isIndexValid(index)) return nullptr;

        std::unique_ptr<CWidget> result {m_slots[index]->m_slottedWidget.content.release()};
        result->outer = nullptr;
        m_slots[index]->markForDestroy();
        return result;
    }

    CSlot* CPanel::addChild(std::unique_ptr<CWidget> child)
    {
        return addChildWithCustomSlot<CSlot>(std::move(child));
    }

    sf::FloatRect CPanel::getLocalBounds() const
    {
        sf::FloatRect result {getPosition(), {0.f, 0.f}};

        for (auto& slot : m_slots)
        {
            result.size += slot->getLocalBounds().size;
        }
        
        return result;
    }

    CSlot* CPanel::addChildWithSlot(std::unique_ptr<CWidget> child, std::unique_ptr<CSlot> slot)
    {
        child->outer = this;
        slot->outer = this;
        slot->setContent(std::move(child));
        m_slots.emplace_back(std::move(slot));
        return m_slots.back().get();
    }

    void CPanel::preTick()
    {
        CWidget::preTick();

        for (const auto& slot : m_slots)
        {
            if (slot->pendingCreate())
            {
                slot->unmarkForCreate();
                if (const auto content = slot->getContent())
                    content->preTick();
            }
        }
    }

    bool CPanel::eventInput(const sf::Event& ev)
    {
        for (const auto& slot : m_slots)
        {
            if (const auto content = slot->getContent())
                if (content->eventInput(ev)) break; // TODO - this probably sucks!
        }

        return CWidget::eventInput(ev);
    }

    void CPanel::tick(const float deltaTime)
    {
        for (const auto& slot : m_slots)
        {
            if (!slot->pendingCreate() && slot->getContent())
            {
                slot->getContent()->tick(deltaTime);
            }
        }
    }

    void CPanel::draw(sf::RenderTarget& target, const sf::RenderStates states) const
    {
        for (size_t i {0}; const auto& slot : m_slots)
        {
            if (!slot->pendingCreate())
            {
                // TODO - decided on if we just use states (and have the last slots' draws stack,
                // or reset it each time so the slot needs to have its own stacking
                auto statesCopy = states;
                slot->drawContent(i, statesCopy);
                // apply the additive transform
                statesCopy.transform *= slot->getContent()->transform;
                target.draw(*slot->getContent(), statesCopy);
            }

            i++;
        }
    }

    void CPanel::postTick()
    {
        CWidget::postTick();

        for (auto it = m_slots.rbegin(); it != m_slots.rend();)
        {
            const auto& slot = *it;
            if (const auto content = slot->getContent())
                content->postTick();

            if (slot->pendingDestroy())
            {
                it = decltype(it)(m_slots.erase(std::next(it).base()));
            }
            else
                ++it;
        }
    }

    CPanel::ConstIterator CPanel::getSlotIterator(CSlot* slot) const
    {
        return std::ranges::find_if(m_slots.begin(), m_slots.end(), [slot](auto& uniqueSlot)
        {
            return uniqueSlot.get() == slot;
        });
    }

    CPanel::ConstIterator CPanel::getSlotIterator(const CWidget* child) const
    {
        return getSlotIterator(child->getSlot());
    }
}
