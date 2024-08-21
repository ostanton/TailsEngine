#ifndef TAILS_WIDGET_HPP
#define TAILS_WIDGET_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include <optional>

namespace tails
{
    class WContainer;
    class WViewport;
    class CEngine;

    /**
     * Base class for all widgets. Derived classes from this are encouraged to prefix
     * with 'W' (e.g. WText), as to avoid naming (like with a potential CText entity)
     */
    class TAILS_API CWidget :
        public CObject,
        public ITickable,
        public sf::Drawable,
        public sf::Transformable
    {
        friend WContainer;
        friend WViewport;

    public:
        [[nodiscard]] WContainer* getParent() const;
        void destroy();
        [[nodiscard]] CEngine& getEngine() const;

        /*
         * Sizing widgets is implemented in their derived classes, allowing for each child
         * to specify how they size (e.g. a sprite doing it via a VertexArray, containers
         * maybe via the sum of its children's sizes, etc.).
         */

        virtual void setSize(const sf::Vector2f& size) {}

        /**
         * Get the size of the widget.
         * @return Possibly valid size
         */
        [[nodiscard]] virtual std::optional<sf::Vector2f> getSize() const {return std::nullopt;}
    };
}

#endif // TAILS_WIDGET_HPP
