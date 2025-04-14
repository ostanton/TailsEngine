#include "Player.hpp"

#include <Tails/Application.hpp>
#include <Tails/EntryPoint.hpp>
#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/String.hpp>
#include <Tails/World/ActorRegistry.hpp>

class CTestActor : public tails::CActor
{
public:
    CTestActor()
    {
        auto const sprite = createComponent<tails::CSpriteComponent>();
        sprite->setSize({32.f, 32.f});
        sprite->setColour(tails::SColour::magenta);
        setRootComponent(sprite);
    }
};

TAILS_REGISTER_ACTOR(CTestActor, "TestActor")

class CTestActor2 : public tails::CActor
{
public:
    CTestActor2()
    {
        auto const sprite = createComponent<tails::CSpriteComponent>();
        sprite->setSize({32.f, 32.f});
        sprite->setColour(tails::SColour::magenta);
        setRootComponent(sprite);
    }
};

TAILS_REGISTER_ACTOR(CTestActor2, "TestActor2")

class CExampleApp final : public tails::IApplication
{
public:
    CExampleApp()
        : IApplication({1280, 720})
    {
    }

private:
    bool init(const int argc, char* argv[]) override
    {
        if (!IApplication::init(argc, argv))
            return false;

        auto const level = tails::world::getLevelFromHandle(0);
        if (!level)
        {
            return false;
        }
        
        //level->spawnActor<CPlayer>({{50.f, 50.f}, 0.f, {1.f, 1.f}});
        //level->spawnActor<CTestActor>({{96.f, 96.f}, 0.f, {1.f, 1.f}});
        auto const player = level->spawnActor(
            "Player",
            {
                {50.f, 50.f},
                0.f,
                {1.f, 1.f}
            },
            -5
        );
        level->spawnActor("TestActor", {{96.f, 96.f}, 0.f, {1.f, 1.f}});
        player->setLayer(5);
        return true;
    }
    
    void onInputEvent(const tails::CEvent& ev) override
    {
        if (ev.is<tails::CEvent::SClosed>())
            exit();
    }
};

TAILS_IMPLEMENT_ENTRY_POINT(CExampleApp, "My GAME!")

