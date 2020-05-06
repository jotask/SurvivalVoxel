#include "system/physics_system/physics_system.hpp"

#include "system/imgui_system.hpp"
#include "system/shader_system/shader_system.hpp"

#include <imgui.h>

namespace engine
{
    PhysicsSystem::PhysicsSystem()
        : m_imguiSystem(nullptr)
        , m_shaderSystem(nullptr)
        , m_renderImgui(false)
        , m_renderDebug(false)
        , m_world(nullptr)
        , m_bulletDebugugger(nullptr)
        , m_collisionConfiguration(nullptr)
        , m_dispatcher(nullptr)
        , m_overlappingPairCache(nullptr)
        , m_solver(nullptr)
    {

    }

    PhysicsSystem::~PhysicsSystem()
    {
        for (auto i = m_world->getNumCollisionObjects() - 1; i >= 0; i--)
        {
            btCollisionObject* obj = m_world->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);
            if (body != nullptr && body->getMotionState())
            {
                delete body->getMotionState();
            }
            m_world->removeCollisionObject(obj);
            delete obj;
        }
        m_collisionShapes.clear();
    }

    bool PhysicsSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();
        return true;
    }

    bool PhysicsSystem::init()
    {

        m_imguiSystem->registerSystem("PhysicsSystem", m_renderImgui);

        auto& shader = m_shaderSystem->getShader("bullet3Shader");

        m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
        m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
        m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();
        m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();
        m_world = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_overlappingPairCache.get(), m_solver.get(), m_collisionConfiguration.get());
        m_bulletDebugugger = std::make_unique<CDebugDraw>(shader);

        m_world->setGravity(c_gravity);

        if(true)
        {
            const auto createGround = true;
            const auto createBall = true;

            if(createGround == true)
            {
                const auto groundSize = 10.;
                 auto groundShape = std::make_unique<btBoxShape>(btVector3(btScalar(groundSize), btScalar(1.), btScalar(groundSize)));

                auto groundTransform = btTransform();
                groundTransform.setIdentity();
                groundTransform.setOrigin(btVector3(0, 0, 0));

                const auto mass = btScalar(0.);
                const auto isDynamic = (mass != 0.f);

                auto localInertia = btVector3(0, 0, 0);
                if (isDynamic == true)
                {
                    groundShape->calculateLocalInertia(mass, localInertia);
                }

                // Using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
                auto* myMotionState = new btDefaultMotionState(groundTransform);
                auto rbInfo = btRigidBody::btRigidBodyConstructionInfo (mass, myMotionState, groundShape.get(), localInertia);
                auto* body = new btRigidBody(rbInfo);

                body->setRestitution(1.f);

                m_collisionShapes.push_back(std::move(groundShape));

                // Add the body to the dynamics world
                m_world->addRigidBody(body);

            }

            if (createBall == true)
            {
                //create a dynamic rigidbody
                auto colShape = std::make_unique<btSphereShape>(btScalar(1.));

                // Create Dynamic Objects
                auto startTransform = btTransform();
                startTransform.setIdentity();
                startTransform.setOrigin(btVector3(0, 5, 0));

                const auto mass = btScalar(1.f);
                const auto isDynamic = (mass != 0.f);

                auto localInertia = btVector3(0, 0, 0);
                if (isDynamic == true)
                {
                    colShape->calculateLocalInertia(mass, localInertia);
                }

                auto* myMotionState = new btDefaultMotionState(startTransform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape.get(), localInertia);
                auto* body = new btRigidBody(rbInfo);

                body->setRestitution(1.f);

                m_collisionShapes.push_back(std::move(colShape));

                m_world->addRigidBody(body);
            }

        }

        m_bulletDebugugger->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
        m_world->setDebugDrawer(m_bulletDebugugger.get());

        return true;
    }

    void PhysicsSystem::preUpdate()
    {

    }

    void PhysicsSystem::update()
    {
        m_world->stepSimulation(1.f / 60.f, 10);
    }

    void PhysicsSystem::postUpdate()
    {

    }

    void PhysicsSystem::preRender()
    {

    }

    void PhysicsSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("PhysicsSystem", &m_renderImgui);
            ImGui::Checkbox("Debug Render Physics", &m_renderDebug);
            ImGui::Text("N. objects: %i", m_world->getNumCollisionObjects());
            ImGui::End();
        }

        if (m_renderDebug == true)
        {
            m_world->debugDrawWorld();
            m_bulletDebugugger->render();
        }
    }

    void PhysicsSystem::postRender()
    {

    }

    void PhysicsSystem::beginFrame()
    {

    }

    void PhysicsSystem::endFrame()
    {
    }

}
