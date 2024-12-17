#include <Tails/Components/ParticleComponent.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace tails
{
    void CParticleComponent::tick(float deltaTime)
    {
        CComponent::tick(deltaTime);

        // TODO - some particle movement or something idk
    }

    void CParticleComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        CTransformComponent::draw(target, states);

        sf::VertexArray vertices {sf::PrimitiveType::Points, m_particles.size()};

        for (size_t i {0}; const auto& vertex : m_particles)
        {
            vertices[i] = vertex;
            i++;
        }
    }
}
