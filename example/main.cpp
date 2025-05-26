#include "MyWidget.hpp"

#include <Tails/Application.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/String.hpp>
#include <Tails/World/ActorRegistry.hpp>
#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/UI/Layout/StackBox.hpp>
#include <Tails/UI/Layout/Canvas.hpp>
#include <Tails/Memory.hpp>
#include <Tails/Log.hpp>
#include <Tails/Templated/StaticArray.hpp>
#include <Tails/Input/Event.hpp>

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

struct STestStruct
{
    STestStruct(const int j)
        : i(j)
    {}
    
    int i {0};
};

namespace
{
    std::shared_ptr<CMyWidget> gMyWidget;

    void pollInputCallback(const tails::CEvent& ev)
    {
        if (auto const keyEv = ev.getIf<tails::CEvent::SKeyDown>())
        {
            if (keyEv->key == tails::EKeys::Escape)
                tails::app::exit();
        }
    }
}

int main(const int argc, char* argv[])
{
    using namespace tails;

    const SWindowInfo windowInfo {
        .title = "My game!",
        .size = {1920, 1080},
        .flags = {EWindowFlags::Resizable, EWindowFlags::Fullscreen}
    };
    if (!app::init(argc, argv, windowInfo))
        return -1;

    // testing shenanigans
    auto const level = world::getCurrentLevel();
    if (!level)
        return 0;

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

    gMyWidget = ui::createWidget<CMyWidget>(ui::getRootPanel());
    const std::vector colours {SColour::magenta, SColour::blue, SColour::green, SColour::red};
    gMyWidget->refreshContents(colours);
    auto const myWidgetSlot = ui::CCanvas::slotAsCanvasSlot(gMyWidget);
    myWidgetSlot->position.x = 16.f;
    myWidgetSlot->position.y = 16.f;

    auto const testStruct = mem::alloc<STestStruct>();
    TAILS_LOG_VA(Game, Message, "Test Struct value: {}", testStruct->i);
    mem::construct(*testStruct, 7);
    TAILS_LOG_VA(Game, Message, "Test Struct value: {}", testStruct->i);
    mem::destroy(testStruct);

    // clang things i is unused! So commenting out for now
    //TStaticArray<int, 5> numbers {4, 2, 6, 4, 8};
    //for (const auto i : numbers)
    //{
    //    TAILS_LOG(Game, Message, TAILS_FMT("Number is: {}", i));
    //}

    // default run sequence
    //app::run();

    // customised run sequence with custom input polling callback (to close the window with the escape key)
    while (!app::shouldExit())
    {
        app::startFrame();
        app::pollInput(pollInputCallback);
        app::tick(app::getCurrentFrameInfo().getDeltaSeconds());
        app::render();
        app::endFrame();
    }

    app::deinit();
    return 0;
}
