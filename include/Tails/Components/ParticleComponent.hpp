#ifndef TAILS_PARTICLE_COMPONENT_HPP
#define TAILS_PARTICLE_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/TransformComponent.hpp>

#include <SFML/Graphics/Vertex.hpp>

#include <vector>

namespace tails
{
    class TAILS_API CParticleComponent : public CTransformComponent
    {
    public:
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
    private:
        std::vector<sf::Vertex> m_particles;
    };
}

#endif // TAILS_PARTICLE_COMPONENT_HPP
