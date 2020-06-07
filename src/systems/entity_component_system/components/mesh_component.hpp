#pragma once

#include "systems/entity_component_system/components/component.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <map>

namespace aiko
{

    class Entity;
    class Mesh;
    class Shader;

    class MeshComponent : public Component
    {
    public:

        MeshComponent(Entity* entity, Mesh* mesh, Shader* shader);
        virtual ~MeshComponent() = default;

        virtual void render() override;

    private:

        Mesh*   m_mesh;
        Shader* m_shader;

    };
}
