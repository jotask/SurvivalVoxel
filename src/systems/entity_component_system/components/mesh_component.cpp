#include "mesh_component.hpp"

#include "systems/entity_component_system/entity.hpp"

#include "systems/assets_system/mesh.hpp"
#include "systems/shader_system/shader.hpp"

namespace aiko
{

    MeshComponent::MeshComponent(Entity* entity, Mesh* mesh, Shader* shader)
        : Component(entity)
        , m_mesh(mesh)
        , m_shader(shader)
    {

    }

    void MeshComponent::render()
    {
        static auto shineDamper = 1.0f;
        static auto reflectivity = 0.0f;

        auto modelMatrix = getEntity()->getTransform().getModelMatrix();
        m_shader->use();
        m_shader->setMat4("model", modelMatrix);
        m_shader->setFloat("shineDamper", shineDamper);
        m_shader->setFloat("reflectivity", reflectivity);
        m_shader->unuse();
        m_mesh->render(*m_shader);
    }

}

