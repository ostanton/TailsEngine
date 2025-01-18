#include <Tails/Components/TransformComponent.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include "Tails/Entity.hpp"

namespace tails
{
    sf::FloatRect CTransformComponent::getLocalBounds() const
    {
        // TODO - this SUCKS!
        sf::FloatRect result;
        for (auto const child : m_children)
        {
            result = child->getTransform().transformRect(result);
        }
        return result;
    }

    sf::FloatRect CTransformComponent::getGlobalBounds() const
    {
        return getTransform().transformRect(getLocalBounds());
    }

    sf::Vector2f CTransformComponent::getGlobalPosition() const
    {
        return m_parent->getTransform().transformPoint(getPosition());
    }

    sf::Angle CTransformComponent::getGlobalRotation() const
    {
        return m_parent->getRotation() + getRotation();
    }

    sf::Vector2f CTransformComponent::getGlobalScale() const
    {
        return {
            (m_parent->getScale().x - 1.f) + (getScale().x - 1.f) + 1.f,
            (m_parent->getScale().y - 1.f) + (getScale().y - 1.f) + 1.f
        };
    }

    void CTransformComponent::setParent(CTransformComponent* parent)
    {
        if (m_parent)
            m_parent->removeChild(this);
        
        parent->addChild(this);
        m_parent = parent;
    }

    std::vector<CTransformComponent*> CTransformComponent::getAllChildren(const bool recursive) const
    {
        std::vector<CTransformComponent*> result {m_children.size()};

        for (auto& child : m_children)
        {
            result.emplace_back(child);
            if (!recursive) continue;
            
            if (child->hasChildren())
            {
                auto childChildren = child->getAllChildren(true);
                result.insert(result.end(), childChildren.begin(), childChildren.end());
            }
        }

        return result;
    }

    bool CTransformComponent::hasChild(CTransformComponent* child) const
    {
        if (child && getChildIterator(child) != m_children.end())
            return true;

        return false;
    }

    bool CTransformComponent::hasChildren() const
    {
        return !m_children.empty();
    }
    
    CTransformComponent::ChildIterator CTransformComponent::getChildIterator(CTransformComponent* child)
    {
        return std::ranges::find(m_children.begin(), m_children.end(), child);
    }

    CTransformComponent::ConstChildIterator CTransformComponent::getChildIterator(CTransformComponent* child) const
    {
        return std::ranges::find(m_children.begin(), m_children.end(), child);
    }

    void CTransformComponent::tick(float deltaTime)
    {
        // child component tick is handled by owning entity
    }

    void CTransformComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // child component draw is handled by owning entity
    }

    CTransformComponent* CTransformComponent::addChild(CTransformComponent* child)
    {
        m_children.emplace_back(child);
        if (auto const parent = child->getParent())
            parent->removeChild(child);
        child->m_parent = this;
        return child;
    }

    bool CTransformComponent::removeChild(CTransformComponent* child)
    {
        // we can erase it from this vector, as it is non-owning. Removing it from the entity requires postTick
        if (const auto it = getChildIterator(child); it != m_children.end())
        {
            m_children.erase(it);
            return true;
        }

        return false;
    }
}
