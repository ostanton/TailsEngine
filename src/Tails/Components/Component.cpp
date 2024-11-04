#include <Tails/Components/Component.hpp>
#include <Tails/Entity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CEntity& CComponent::getOwningEntity() const
    {
        // components should never not have a valid owning entity
        return *getTypedOuter<CEntity>();
    }

    sf::Vector2f CComponent::getGlobalPosition() const
    {
        return m_parent->getTransform().transformPoint(getPosition());
    }

    sf::Angle CComponent::getGlobalRotation() const
    {
        return m_parent->getRotation() + getRotation();
    }

    sf::Vector2f CComponent::getGlobalScale() const
    {
        return {
            (m_parent->getScale().x - 1.f) + (getScale().x - 1.f) + 1.f,
            (m_parent->getScale().y - 1.f) + (getScale().y - 1.f) + 1.f
        };
    }

    CComponent* CComponent::createRegisteredComponent(std::string_view className)
    {
        return addChild(std::unique_ptr<CComponent>(newObject<CComponent>(className, outer)));
    }

    std::vector<CComponent*> CComponent::getAllChildren(bool recursive) const
    {
        std::vector<CComponent*> result {m_children.size()};

        for (auto& child : m_children)
        {
            result.emplace_back(child.get());
            if (!recursive) continue;
            
            if (child->hasChildren())
            {
                auto childChildren = child->getAllChildren(true);
                result.insert(result.end(), childChildren.begin(), childChildren.end());
            }
        }

        return result;
    }

    void CComponent::destroyChild(CComponent* child, bool recursive)
    {
        if (!child) return;

        child->markForDestroy();
        child->destroy();

        for (auto& newChild : child->m_children)
        {
            if (!recursive)
            {
                // mark for create so tick & draw don't use them this frame
                newChild->markForCreate();
                m_children.emplace_back(std::move(newChild));
            }
            else
                child->destroyChild(newChild.get(), true);
        }
    }

    bool CComponent::hasChild(CComponent* child) const
    {
        if (child && getChildIterator(child) != m_children.end())
            return true;

        return false;
    }

    bool CComponent::hasChildren() const
    {
        return !m_children.empty();
    }

    void CComponent::preTick()
    {
        ITickable::preTick();

        for (const auto& child : m_children)
        {
            child->preTick();
            
            if (child->pendingCreate())
            {
                child->unmarkForCreate();
                child->postCreate();
            }
        }
    }

    void CComponent::tick(float deltaTime)
    {
        for (const auto& child : m_children)
            if (!child->pendingCreate())
                child->tick(deltaTime);
    }

    void CComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (const auto& child : m_children)
            if (!child->pendingCreate())
                target.draw(*child, states);
    }

    void CComponent::postTick()
    {
        ITickable::postTick();

        for (auto it = m_children.rbegin(); it != m_children.rend();)
        {
            it->get()->postTick();

            if (it->get()->pendingDestroy())
                it = decltype(it)(m_children.erase(std::next(it).base()));
            else
                ++it;
        }
    }

    CComponent::ChildIterator CComponent::getChildIterator(CComponent* child)
    {
        return std::ranges::find_if(m_children.begin(), m_children.end(), [child](auto& uniqueChild)
        {
            return uniqueChild.get() == child;
        });
    }

    CComponent::ConstChildIterator CComponent::getChildIterator(CComponent* child) const
    {
        return std::ranges::find_if(m_children.begin(), m_children.end(), [child](auto& uniqueChild)
        {
            return uniqueChild.get() == child;
        });
    }

    CComponent* CComponent::addChild(std::unique_ptr<CComponent> child)
    {
        child->m_parent = this;
        m_children.emplace_back(std::move(child));
        return m_children.back().get();
    }
}
