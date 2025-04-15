#ifndef TAILS_CAMERA_ACTOR_HPP
#define TAILS_CAMERA_ACTOR_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Actor.hpp>

namespace tails
{
    class CCameraComponent;

    /**
     * Simple actor wrapper for a single camera component. Generally just used as a default camera
     */
    class TAILS_API CCameraActor : public CActor
    {
    public:
        CCameraActor();
        
        CCameraComponent* cameraComponent;
    };
}

#endif // TAILS_CAMERA_ACTOR_HPP
