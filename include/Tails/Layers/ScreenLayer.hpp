#ifndef TAILS_SCREENLAYER_HPP
#define TAILS_SCREENLAYER_HPP

#include <Tails/Config.hpp>
#include <Tails/Layers/Layer.hpp>

namespace tails
{
    class Widget;
    class WidgetNavigation;

    // a screen is like a level, but except for housing entities, it houses a single root widget
    // if expanded to house more, it should have its own ScreenSlot also
    // a screen stretches its content to fit its camera view size, so normally the content is some kind of panel
    // each screen may also have a navigation member which managers which widget is focused, etc.
    class TAILS_API ScreenLayer : public Layer
    {
    public:
        ScreenLayer();
        ~ScreenLayer() override;

        Widget* setContent(std::unique_ptr<Widget> content);

        template<typename T>
        T* setContent()
        {
            static_assert(std::is_base_of_v<Widget, T>, "Failed to set screen content, type does not derive Widget.");
            return static_cast<T*>(setContent(std::make_unique<T>()));
        }

        [[nodiscard]] Widget* getContent() const;

        // returned content may have failed a cast so could be null!
        template<typename T>
        T* getContent()
        {
            static_assert(std::is_base_of_v<Widget, T>, "Failed to get screen content, type does not derive Widget.");
            return static_cast<T*>(getContent());
        }

        virtual std::unique_ptr<WidgetNavigation> setupWidgetNavigation();
        WidgetNavigation& getNavigation();

    protected:
        void init(State& state) override;
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

    private:
        std::unique_ptr<Widget> m_content;
        std::unique_ptr<WidgetNavigation> m_navigation;
    };
}

#endif // TAILS_SCREENLAYER_HPP
