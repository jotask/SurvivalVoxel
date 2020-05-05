#pragma once

#include "system/system_interface.hpp"
#include "system/physics_debug_renderer.hpp"
#include "utils/shared.hpp"

#include <btBulletDynamicsCommon.h>

#include <vector>

namespace engine
{

    class ImguiSystem;

    class PhysicsSystem : public System
    {
    public:

        PhysicsSystem();
        virtual ~PhysicsSystem() override;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        virtual void beginFrame() override;
        virtual void endFrame() override;

    private:

        const btVector3 c_gravity = { 0, 0, 0 };

        ImguiSystem* m_imguiSystem;
        bool m_renderImgui;
        bool m_renderDebug;

        AikoUPtr<btDiscreteDynamicsWorld> m_world;
        AikoUPtr<CDebugDraw> m_bulletDebugugger;
        AikoUPtr<btDefaultCollisionConfiguration> m_collisionConfiguration;
        AikoUPtr<btCollisionDispatcher> m_dispatcher;
        AikoUPtr<btBroadphaseInterface> m_overlappingPairCache;
        AikoUPtr<btSequentialImpulseConstraintSolver> m_solver;

        std::vector<AikoUPtr<btCollisionShape>> m_collisionShapes;

    };

}
