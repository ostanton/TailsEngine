#ifndef TAILS_CAMERA_COMPONENT_HPP
#define TAILS_CAMERA_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/Component.hpp>

#include <SFML/Graphics/View.hpp>

namespace tails
{
    class TAILS_API CCameraComponent : public CComponent
    {
    public:
        [[nodiscard]] sf::View& getCameraView() {return m_view;}
        [[nodiscard]] const sf::View& getCameraView() const {return m_view;}
        
        void activate();

        [[nodiscard]] bool isActive() const;

        void setLag(float lag);
        [[nodiscard]] float getLag() const {return m_lag;}
        
    private:
        void create() override;
        
        void tick(float deltaTime) override;
        
        sf::View m_view;
        float m_lag {0.f};
    };
}
TAILS_REGISTER_CLASS(CCameraComponent)

#endif // TAILS_CAMERA_COMPONENT_HPP
