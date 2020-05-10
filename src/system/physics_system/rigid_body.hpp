#pragma once

#include "system/entity_component_system/components/component.hpp"

#include "system/physics_system/rigid_body_data.hpp"

namespace engine
{

    class Entity;

    class RigidBody : public Component
    {
    public:

        RigidBody(Entity* entity, physics::RigidBodyData data);

    private:

        physics::RigidBodyData m_data;
        AikoUPtr<btTriangleMesh> m_triangleMesh;

    };

}