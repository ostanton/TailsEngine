#include <Tails/UI/PanelWidget.hpp>
#include <Tails/UI/PanelSlot.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <algorithm>

namespace tails
{
    PanelSlot* PanelWidget::addChild(std::unique_ptr<Widget> content)
    {
        return addChild<PanelSlot>(std::move(content));
    }

    bool PanelWidget::hasChild(Widget* content)
    {
        if (getChildIterator(content) != m_slots.end())
        {
            return true;
        }

        return false;
    }

    bool PanelWidget::removeChild(Widget* content)
    {
        if (auto it = getChildIterator(content); it != m_slots.end())
        {
            (*it)->markForDestroy();
            return true;
        }

        return false;
    }

    bool PanelWidget::removeChildAt(size_t index)
    {
        // check if index exists
        if (index >= m_slots.size()) return false;

        m_slots[index]->markForDestroy();
        return true;
    }

    Widget* PanelWidget::getChildAt(size_t index)
    {
        if (index >= m_slots.size()) return nullptr;

        return m_slots[index]->getContent();
    }

    size_t PanelWidget::getChildIndex(Widget* content)
    {
        if (auto it = getChildIterator(content); it != m_slots.end())
        {
            return it - m_slots.end();
        }

        return -1;
    }

    size_t PanelWidget::getChildrenCount()
    {
        return m_slots.size();
    }

    std::vector<std::unique_ptr<PanelSlot>>::iterator PanelWidget::getChildIterator(Widget* content)
    {
        return std::find_if(m_slots.begin(), m_slots.end(),
        [&](auto& uniqueSlot)
        {
            return uniqueSlot->getContent() == content;
        });
    }

    void PanelWidget::preTick()
    {
        for (auto& childSlot : m_slots)
        {
            childSlot->preTick();

            if (childSlot->pendingCreate)
                childSlot->pendingCreate = false;
        }
    }

    void PanelWidget::tick(float deltaTime)
    {
        for (auto& childSlot : m_slots)
        {
            if (!childSlot->pendingCreate)
                childSlot->tick(deltaTime);
        }
    }

    void PanelWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& childSlot : m_slots)
        {
            if (!childSlot->pendingCreate)
                target.draw(*childSlot, states);
        }
    }

    void PanelWidget::postTick()
    {
        for (size_t i {0}; i < m_slots.size();)
        {
            m_slots[i]->postTick();

            if (m_slots[i]->pendingDestroy)
            {
                m_slots.erase(m_slots.begin() + i);
            }
            else
                i++;
        }
    }
}
