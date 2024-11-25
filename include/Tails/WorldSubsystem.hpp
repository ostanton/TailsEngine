#ifndef TAILS_WORLD_SUBSYSTEM_HPP
#define TAILS_WORLD_SUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Subsystem.hpp>
#include <Tails/World.hpp>

#include <LDtkLoader/Project.hpp>

namespace tails
{
    class TAILS_API CWorldSubsystem final : public CSubsystem
    {
    public:
        CWorldSubsystem();
        
        void openLDtkProject(const std::filesystem::path& path);
        void openLDtkProject(const std::filesystem::path& path, const std::string& initialWorld);

        [[nodiscard]] CWorld& getWorld() noexcept {return m_world;}
        [[nodiscard]] const CWorld& getWorld() const noexcept {return m_world;}
        
    private:
        void init() override;
        void preTick() override;
        void tick(float deltaTime) override;
        void postTick() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        CWorld m_world;
        ldtk::Project m_ldtkProject;
    };
}

#endif // TAILS_WORLD_SUBSYSTEM_HPP
