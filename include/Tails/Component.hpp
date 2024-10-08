#ifndef TAILS_COMPONENT_HPP
#define TAILS_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace tails
{
    class CEntity;
    
    class TAILS_API CComponent :
        public CObject,
        public ITickable,
        public sf::Drawable,
        public sf::Transformable
    {
        friend CEntity;
        
    public:
        [[nodiscard]] virtual sf::FloatRect getGlobalBounds() const {return {};}

        [[nodiscard]] CEntity& getOwningEntity() const;

        [[nodiscard]] sf::Vector2f getGlobalPosition() const;
        [[nodiscard]] sf::Angle getGlobalRotation() const;
        [[nodiscard]] sf::Vector2f getGlobalScale() const;

    protected:
        virtual void create() {}
        virtual void postCreate() {}
        virtual void destroy() {}
    };
}

#endif // TAILS_COMPONENT_HPP
