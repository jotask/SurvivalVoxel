#pragma once

#include "utils/shared.hpp"

#include <btBulletDynamicsCommon.h>

namespace engine
{
    namespace physics
    {

        class RigidBodyData
        {
        public:

            RigidBodyData()
                : mass (btScalar(0.f))
                , m_restitution(1.f)
            {

            }

            float mass;
            float m_restitution;
        };
    }
}
