#ifndef TAILS_MYSCREEN_HPP
#define TAILS_MYSCREEN_HPP

#include <Tails/Layers/ScreenLayer.hpp>

using namespace tails;

class MyScreen : public ScreenLayer
{
    void init(tails::State &state) override;
};

#endif //TAILS_MYSCREEN_HPP
