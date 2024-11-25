#ifndef TAILS_WORLD_HPP
#define TAILS_WORLD_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <string>
#include <memory>
#include <vector>

namespace ldtk
{
    class World;
}

namespace tails
{
    class CEngine;
    class CWorldSubsystem;
    class CLevel;
    
    class TAILS_API CWorld final : public CObject, public ITickable, public sf::Drawable
    {
        friend CWorldSubsystem;

    public:
        CWorld(const CWorld&) = delete;
        CWorld(CWorld&&) noexcept = default;
        CWorld& operator=(const CWorld&) = delete;
        CWorld& operator=(CWorld&&) noexcept = default;
        ~CWorld() override;

        /**
         * Opens a level from its name in the world
         * @param name Level name in world
         * @param closePrevious Whether to close the previously opened level (useful for having only one open at a time)
         * @return The opened level reference
         */
        CLevel& openLevel(const std::string& name, bool closePrevious = true);
        bool closeLevel(CLevel* level);
        bool closeLevel(size_t index);

        [[nodiscard]] CEngine& getEngine() const;
        [[nodiscard]] CLevel* getLevel(size_t index);
        [[nodiscard]] const CLevel* getLevel(size_t index) const;
        [[nodiscard]] CLevel* getLevel(std::string_view name);
        [[nodiscard]] const CLevel* getLevel(std::string_view name) const;
        
    private:
        CWorld();

        void setLDtkWorld(const ldtk::World* world);
        
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        std::vector<CLevel> m_openLevels;
        const ldtk::World* m_world {nullptr};
    };
}

#endif // TAILS_WORLD_HPP
