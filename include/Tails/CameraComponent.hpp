#ifndef TAILS_CAMERA_COMPONENT_HPP
#define TAILS_CAMERA_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Component.hpp>

#include <SFML/Graphics/View.hpp>

namespace tails
{
    class TAILS_API CCameraComponent : public CComponent
    {
    public:
        [[nodiscard]] sf::View& getCameraView() {return m_view;}
        [[nodiscard]] const sf::View& getCameraView() const {return m_view;}
        
        void setActive();

        [[nodiscard]] bool isActive() const;
        
    private:
        void create() override;
        
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        sf::View m_view;
    };
}
TAILS_REGISTER_CLASS(CCameraComponent)

#endif // TAILS_CAMERA_COMPONENT_HPP
