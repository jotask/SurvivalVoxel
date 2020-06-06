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
    class Model;

    class ModelComponent : public Component
    {
    public:

        ModelComponent(Entity* entity, Model* model);
        virtual ~ModelComponent() = default;

        virtual void render() override;

    private:

        Model* m_model;

    };
}
