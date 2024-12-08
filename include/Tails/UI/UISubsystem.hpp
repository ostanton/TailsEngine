#ifndef TAILS_UI_MANAGER_HPP
#define TAILS_UI_MANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Subsystem.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/ResourceManager.hpp>

#include <memory>

namespace sf
{
    class Event;
}

namespace tails::ui
{
    class CPanel;
    class CNavigation;
    
    /**
     * General manager for a game's user interface. It has a root widget which the rest of the tree stems.
     * It ticks, draws, etc. all the widgets in the game.
     *
     * This class receives window inputs before anything else, so for that fraction of time you receive the input,
     * you can do whatever, even if the input is to close the window.
     */
    class TAILS_API CUISubsystem final : public CSubsystem
    {
    public:
        CUISubsystem();
        CUISubsystem(const CUISubsystem&) = delete;
        CUISubsystem& operator=(const CUISubsystem&) = delete;
        ~CUISubsystem() override;
        
        [[nodiscard]] CPanel& getRootWidget() const noexcept;

        template<Derives<CNavigation> NavT>
        NavT* setNavigationClass()
        {
            m_navigation = std::make_unique<NavT>(this);
            return static_cast<NavT*>(m_navigation.get());
        }

        [[nodiscard]] CNavigation& getNavigation() noexcept {return *m_navigation;}
        [[nodiscard]] const CNavigation& getNavigation() const noexcept {return *m_navigation;}

        CResourceManager resourceManager;
        
    private:
        CUISubsystem(CUISubsystem&&) noexcept;
        CUISubsystem& operator=(CUISubsystem&&) noexcept;

        void init() override;
        
        void preTick() override;
        void inputEvent(const sf::Event& ev) override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;
        
        std::unique_ptr<CPanel> m_rootWidget; // TODO - could just be stack allocated, must always be valid
        std::unique_ptr<CNavigation> m_navigation;
    };
}

#endif // TAILS_UI_MANAGER_HPP
