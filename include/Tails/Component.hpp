#ifndef TAILS_COMPONENT_HPP
#define TAILS_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Serialisable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace tails
{
    class CEntity;
    
    class TAILS_API CComponent :
        public CObject,
        public ITickable,
        public ISerialisable,
        public sf::Drawable,
        public sf::Transformable
    {
        friend CEntity;
        
    public:
        [[nodiscard]] virtual sf::FloatRect getGlobalBounds() const {return {};}

        [[nodiscard]] CEntity* getOwningEntity() const;

    protected:
        virtual void create() {}
        virtual void destroy() {}
    };
}

#endif // TAILS_COMPONENT_HPP
