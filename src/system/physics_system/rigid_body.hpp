#pragma once

#include "system/entity_component_system/components/component.hpp"

namespace engine
{

    class Entity;

    class RigidBody : public Component
    {
    public:

        RigidBody(Entity* entity);

    private:

    };

}