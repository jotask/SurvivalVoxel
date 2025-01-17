#pragma once

#include <systems/entity_component_system/entity.hpp>
#include <systems/entity_component_system/components/component.hpp>

#include <glm/glm.hpp>

namespace aiko
{

    class Entity;

    class Light : public Component
    {

    public:

        Light(Entity* entity)
            : Component(entity)
        {

        }

        glm::vec3 position;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 color;

    };
}