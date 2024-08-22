#include <Tails/WidgetContainer.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CWidget* WContainer::addChild(std::unique_ptr<CWidget> widget)
    {
        m_children.emplace_back(std::move(widget));
        CWidget* result {m_children.back().get()};

        result->outer = this;

        return result;
    }

    CWidget* WContainer::getChildAt(size_t index) const
    {
        if (index >= m_children.size()) return nullptr;

        return m_children[index].get();
    }

    std::optional<size_t> WContainer::getChildIndex(CWidget* child) const
    {
        if (auto it = getChildIterator(child); it != m_children.end())
            return std::make_optional(it - m_children.begin());

        return std::nullopt;
    }

    WContainer::ChildVector::const_iterator WContainer::getChildIterator(CWidget* child) const
    {
        return std::find_if(m_children.begin(), m_children.end(),
            [&](auto& uniqueChild)
            {
                return uniqueChild.get() == child;
            });
    }

    void WContainer::destroyChild(CWidget* child)
    {
        if (getChildIterator(child) != m_children.end())
            child->destroy();
    }

    void WContainer::preTick()
    {
        ITickable::preTick();

        for (auto& child : m_children)
        {
            child->preTick();

            if (child->pendingCreate())
            {
                child->unmarkForCreate();
                // TODO - widget life-cycle functions
            }
        }
    }

    void WContainer::tick(float deltaTime)
    {
        for (auto& child : m_children)
        {
            if (!child->pendingCreate())
                child->tick(deltaTime);
        }
    }

    void WContainer::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        for (size_t i {0}; i < m_children.size(); i++)
        {
            if (!m_children[i]->pendingCreate())
            {
                drawChild(i);
                target.draw(*m_children[i], states);
            }
        }
    }

    void WContainer::postTick()
    {
        for (auto it = m_children.rbegin(); it != m_children.rend();)
        {
            (*it)->postTick();

            if ((*it)->pendingDestroy())
                it = decltype(it)(m_children.erase(std::next(it).base()));
            else
                ++it;
        }
    }
}
