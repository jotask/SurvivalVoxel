#include "model_component.hpp"

#include "systems/entity_component_system/entity.hpp"

#include "systems/assets_system/model.hpp"

namespace aiko
{

    ModelComponent::ModelComponent(Entity* entity, Model* model)
        : Component(entity)
        , m_model(model)
    {

    }

    void ModelComponent::render()
    {
        auto modelMatrix = getEntity()->getTransform().getModelMatrix();
        m_model->render(modelMatrix);
    }

}

