#include "Player.hpp"

#include <Tails/Application.hpp>
#include <Tails/EntryPoint.hpp>
#include <Tails/Game/Components/SpriteComponent.hpp>

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

        getLevel().spawnActor<CPlayer>({{50.f, 50.f}, 0.f, {1.f, 1.f}});
        getLevel().spawnActor<CTestActor>({{96.f, 96.f}, 0.f, {1.f, 1.f}});
        return true;
    }
    
    void onInputEvent(const tails::CEvent& ev) override
    {
        if (ev.is<tails::CEvent::SClosed>())
            exit();
    }
};

TAILS_IMPLEMENT_ENTRY_POINT(CExampleApp, "My GAME!")
