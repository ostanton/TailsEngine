#include "MyWidget.hpp"

#include <Tails/Application.hpp>
#include <Tails/EntryPoint.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/String.hpp>
#include <Tails/World/ActorRegistry.hpp>
#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/UI/Layout/StackBox.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/UI/Layout/Canvas.hpp>

class CTestActor : public tails::CActor
{
public:
    CTestActor()
    {
        auto const sprite = createComponent<tails::CSpriteComponent>();
        sprite->size = {32.f, 32.f};
        sprite->colour = tails::SColour::magenta;
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
        sprite->size = {32.f, 32.f};
        sprite->colour = tails::SColour::magenta;
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

        auto const level = tails::world::getCurrentLevel();
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

        using namespace tails::ui;
        using namespace tails;
        const auto myWidget = createWidget<CMyWidget>(getRootPanel());
        const std::vector colours {SColour::magenta, SColour::blue, SColour::green, SColour::red};
        myWidget->refreshContents(colours);
        auto const myWidgetSlot = CCanvas::slotAsCanvasSlot(myWidget);
        myWidgetSlot->position.x = 16.f;
        myWidgetSlot->position.y = 16.f;
        return true;
    }
    
    void onInputEvent(const tails::CEvent& ev) override
    {
        if (ev.is<tails::CEvent::SClosed>())
            exit();
    }
};

TAILS_IMPLEMENT_ENTRY_POINT(CExampleApp, "My GAME!")
