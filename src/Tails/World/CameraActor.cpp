#include <Tails/World/CameraActor.hpp>
#include <Tails/World/Components/CameraComponent.hpp>

namespace tails
{
    CCameraActor::CCameraActor()
    {
        cameraComponent = createComponent<CCameraComponent>();
        setRootComponent(cameraComponent);
    }
}
