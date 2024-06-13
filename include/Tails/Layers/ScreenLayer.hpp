#ifndef TAILS_SCREENLAYER_HPP
#define TAILS_SCREENLAYER_HPP

#include <Tails/Config.hpp>
#include <Tails/Layers/Layer.hpp>

namespace tails
{
    class Widget;

    // a screen is like a level, but except for housing entities, it houses a single root widget
    // if expanded to house more, it should have its own ScreenSlot also
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

    protected:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

    private:
        std::unique_ptr<Widget> m_content;
    };
}

#endif // TAILS_SCREENLAYER_HPP
