#ifndef TAILS_LEVEL_SUBSYSTEM_HPP
#define TAILS_LEVEL_SUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Subsystem.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class CLevel;
    struct SLoadParams;
    struct SLDtkLoadParams;
    
    class TAILS_API CLevelSubsystem final : public CSubsystem
    {
    public:
        using LevelVector = std::vector<std::unique_ptr<CLevel>>;
        using LevelIterator = LevelVector::iterator;
        using ConstLevelIterator = LevelVector::const_iterator;

        CLevel* loadLDtkLevel(const SLDtkLoadParams& params, CLevel* parent = nullptr, bool closeOthers = true);

        template<Derives<SLoadParams> ParamsT, typename FuncT>
        CLevel* loadLevelCustom(ParamsT loadParams, FuncT func, CLevel* parent = nullptr, const bool closeOthers = true)
        {
            return setupLevel(func(loadParams), parent, closeOthers);
        }
        
        void closeLevel(CLevel* level);
        void closeAllLevels();
        void closeAllLevelsExcept(const CLevel* exceptionLevel);
        
    private:
        /**
         * Sets up an already created and initialised level. All this does is set the subsystem to be the level's
         * owner, setup the outer chain, and the level's default view. It should only be called in a wrapper
         * function for loading a level from some third party thing like LDtk or Tiled.
         * @param level Level to setup
         * @param parent Optional parent level
         * @param closeOthers Whether to close all other levels before setting up this level
         * @return Setup level
         */
        CLevel* setupLevel(std::unique_ptr<CLevel> level, CLevel* parent = nullptr, bool closeOthers = true);
        
        void init() override;
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        LevelIterator getLevelIterator(CLevel* level);
        ConstLevelIterator getLevelIterator(CLevel* level) const;

        LevelVector m_levels;
    };
}

#endif // TAILS_LEVEL_SUBSYSTEM_HPP
