#include "test_state.hpp"

#include "systems/assets_system/assets_system.hpp"
#include "systems/entity_component_system/entity_component_system.hpp"
#include "systems/entity_component_system/entity.hpp"
#include "systems/entity_component_system/components/model_component.hpp"
#include "engine.hpp"

namespace aiko
{

    bool TestState::onEnter()
    {

        auto& engine = Engine::getInstance();

        auto* ecs = engine.getSystem<EntityComponentSystem>();
        auto* assetsSystem = engine.getSystem<AssetsSystem>();

        auto& assetModels = assetsSystem->getAssets(AssetType::Model);

        if (assetModels.empty() == false)
        {

            auto& e = ecs->addEntity();
            e.getTransform().scale *= 2.f;

            auto* model = static_cast<Model*>(assetModels[assetModels.size() - 1].get());

            model->load();

            e.addComponent<ModelComponent>(model);
        }

        return true;
    }

    bool TestState::onUpdate(GameStateManagerSystem* gsm)
    {
        return true;
    }

    bool TestState::onExit()
    {
        return true;
    }

}