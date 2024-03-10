#pragma once
#include "TailsEngine/Managers/Input/InputActionModifier.h"

namespace tails
{
class DeadZoneModifier : public InputActionModifier
{
public:
    float lowerThreshold {0.2f};
    float upperThreshold {1.f};
};

}
