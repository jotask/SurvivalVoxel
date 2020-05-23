#pragma once

#include "systems/system_interface.hpp"
#include "systems/physics_system/physics_debug_renderer.hpp"
#include "utils/shared.hpp"

#include <btBulletDynamicsCommon.h>

#include <vector>

namespace engine
{

    class ImguiSystem;
    class ShaderSystem;

    class PhysicsSystem : public System
    {
    public:

        PhysicsSystem();
        virtual ~PhysicsSystem() override;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        virtual void beginFrame() override;
        virtual void endFrame() override;

        void addRigidBodyToWorld(btRigidBody* body);

    private:

        const btVector3 c_gravity = { 0, -10, 0 };

        ImguiSystem* m_imguiSystem;
        ShaderSystem* m_shaderSystem;
        bool m_renderImgui;
        bool m_renderDebug;

        AikoUPtr<btDiscreteDynamicsWorld> m_world;
        AikoUPtr<CDebugDraw> m_bulletDebugugger;
        AikoUPtr<btDefaultCollisionConfiguration> m_collisionConfiguration;
        AikoUPtr<btCollisionDispatcher> m_dispatcher;
        AikoUPtr<btBroadphaseInterface> m_overlappingPairCache;
        AikoUPtr<btSequentialImpulseConstraintSolver> m_solver;

    };

}
