#ifndef TAILS_UI_MANAGER_HPP
#define TAILS_UI_MANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Concepts.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <memory>

namespace sf
{
    class Event;
}

namespace tails
{
    class CEngine;
}

namespace tails::ui
{
    class CWidget;
    class CNavigation;
    
    /**
     * General manager for a game's user interface. It has a root widget which the rest of the tree stems.
     * It ticks, draws, etc. all the widgets in the game.
     *
     * This class receives window inputs before anything else, so for that fraction of time you receive the input,
     * you can do whatever, even if the input is to close the window.
     */
    class TAILS_API CUIManager final : public CObject, public ITickable, public sf::Drawable
    {
        friend CEngine;
        
    public:
        CUIManager(const CUIManager&) = delete;
        CUIManager& operator=(const CUIManager&) = delete;
        ~CUIManager() override;
        
        template<Derives<CWidget> WidgetT, typename... ArgsT>
        requires ConstructibleUserType<WidgetT, ArgsT...>
        WidgetT* setRootWidget(ArgsT&&... args)
        {
            return static_cast<WidgetT*>(setRootWidgetImpl(std::make_unique<WidgetT>(std::forward<ArgsT>(args)...)));
        }

        [[nodiscard]] CWidget* getRootWidget() const noexcept {return m_rootWidget.get();}

        template<Derives<CNavigation> NavT>
        NavT* setNavigationClass()
        {
            m_navigation = std::make_unique<NavT>(this);
            return static_cast<NavT*>(m_navigation.get());
        }

        [[nodiscard]] CNavigation& getNavigation() noexcept {return *m_navigation;}
        [[nodiscard]] const CNavigation& getNavigation() const noexcept {return *m_navigation;}
        
    private:
        CUIManager();
        CUIManager(CUIManager&&) noexcept;
        CUIManager& operator=(CUIManager&&) noexcept;
        
        CWidget* setRootWidgetImpl(std::unique_ptr<CWidget> widget);

        void preTick() override;
        void eventInput(const sf::Event& ev) const;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;
        
        std::unique_ptr<CWidget> m_rootWidget;
        std::unique_ptr<CNavigation> m_navigation;
    };
}

#endif // TAILS_UI_MANAGER_HPP