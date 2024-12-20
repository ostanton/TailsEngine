#ifndef TAILS_LEVEL_SUBSYSTEM_HPP
#define TAILS_LEVEL_SUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Subsystem.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class CLevel;
    
    class TAILS_API CLevelSubsystem final : public CSubsystem
    {
    public:
        using LevelVector = std::vector<std::unique_ptr<CLevel>>;
        using LevelIterator = LevelVector::iterator;
        using ConstLevelIterator = LevelVector::const_iterator;
        
        CLevel* openLevel(std::string_view name, CLevel* parent = nullptr);
        void closeLevel(CLevel* level);
        
    private:
        void init() override;
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;
        
        LevelIterator getLevelIterator(CLevel* level);
        ConstLevelIterator getLevelIterator(CLevel* level) const;
        
        std::vector<std::unique_ptr<CLevel>> m_levels;
    };
}

#endif // TAILS_LEVEL_SUBSYSTEM_HPP
