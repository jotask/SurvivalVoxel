#include "system/physics_system/physics_system.hpp"

#include "system/imgui_system.hpp"
#include "system/shader_system/shader_system.hpp"
#include "system/entity_component_system/entity.hpp"

#include "system/physics_system/rigid_body_converter.hpp"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

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
            delete body->getCollisionShape();
            m_world->removeCollisionObject(obj);
            delete obj;
        }
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
            const auto createBall = false;

            if(createGround == true)
            {
                const auto groundSize = 10.;
                 auto* groundShape = new btBoxShape(btVector3(btScalar(groundSize), btScalar(1.), btScalar(groundSize)));

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
                auto rbInfo = btRigidBody::btRigidBodyConstructionInfo (mass, myMotionState, groundShape, localInertia);
                auto* body = new btRigidBody(rbInfo);

                body->setRestitution(1.f);

                // Add the body to the dynamics world
                m_world->addRigidBody(body);

            }

            if (createBall == true)
            {
                //create a dynamic rigidbody
                auto* colShape = new btSphereShape(btScalar(1.));

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
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
                auto* body = new btRigidBody(rbInfo);

                body->setRestitution(1.f);

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
    }

    void PhysicsSystem::postUpdate()
    {
        m_world->stepSimulation(1.f / 60.f, 10);
        for (int i = m_world->getNumCollisionObjects() - 1; i >= 0; i--)
        {

            auto* obj = m_world->getCollisionObjectArray()[i];
            auto* body = btRigidBody::upcast(obj);
            auto* entity = static_cast<Entity*>(body->getUserPointer());
            if (entity == nullptr) continue;

            btTransform trans;
            if (body != nullptr && body->getMotionState())
            {
                body->getMotionState()->getWorldTransform(trans);
            }
            else
            {
                trans = obj->getWorldTransform();
            }

            auto tmp = physics::converter::bulletToGlm(trans);

            glm::mat4 transformation; // your transformation matrix.
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(transformation, scale, rotation, translation, skew, perspective);
            rotation = glm::conjugate(rotation);

            entity->getTransform().position = physics::converter::bulletToGlm(trans.getOrigin());
            entity->getTransform().rotation = glm::eulerAngles(rotation) * 3.14159f / 180.f;

            printf("world pos object %d = %f,%f,%f\n", i, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
        }
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

    void PhysicsSystem::addRigidBodyToWorld(btRigidBody * body)
    {
        m_world->addRigidBody(body);
    }

}
