#include <Tails/WorldSubsystem.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CWorldSubsystem::CWorldSubsystem()
    {
        m_world.outer = this;
    }

    void CWorldSubsystem::openLDtkProject(const std::filesystem::path& path)
    {
        m_ldtkProject.loadFromFile(path.string());
        m_world.setLDtkWorld(&m_ldtkProject.getWorld());
    }

    void CWorldSubsystem::openLDtkProject(const std::filesystem::path& path, const std::string& initialWorld)
    {
        m_ldtkProject.loadFromFile(path.string());
        m_world.setLDtkWorld(&m_ldtkProject.getWorld(initialWorld));
    }

    void CWorldSubsystem::init()
    {
        
    }

    void CWorldSubsystem::preTick()
    {
        CSubsystem::preTick();

        m_world.preTick();
    }

    void CWorldSubsystem::tick(const float deltaTime)
    {
        m_world.tick(deltaTime);
    }

    void CWorldSubsystem::postTick()
    {
        CSubsystem::postTick();

        m_world.postTick();
    }

    void CWorldSubsystem::draw(sf::RenderTarget& target, const sf::RenderStates states) const
    {
        target.draw(m_world, states);
    }
}
