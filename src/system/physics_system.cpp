#include "system/physics_system.hpp"

#include "system/imgui_system.hpp"

#include <imgui.h>

namespace engine
{
    PhysicsSystem::PhysicsSystem()
        : m_imguiSystem(nullptr)
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

    bool PhysicsSystem::init()
    {

        m_imguiSystem->registerSystem("PhysicsSystem", m_renderImgui);

        {
        
            m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
            m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
            m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();
            m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();
            m_world = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_overlappingPairCache.get(), m_solver.get(), m_collisionConfiguration.get());
            m_bulletDebugugger = std::make_unique<CDebugDraw>();

            m_world->setGravity(c_gravity);


            //the ground is a cube of side 100 at position y = -56.
            //the sphere will hit it at y = -6, with center at -5
            {
                 auto groundShape = std::make_unique<btBoxShape>(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

                m_collisionShapes.push_back(std::move(groundShape));

                btTransform groundTransform;
                groundTransform.setIdentity();
                groundTransform.setOrigin(btVector3(0, -56, 0));

                btScalar mass(0.);

                //rigidbody is dynamic if and only if mass is non zero, otherwise static
                const auto isDynamic = (mass != 0.f);

                btVector3 localInertia(0, 0, 0);
                if (isDynamic == true)
                {
                    groundShape->calculateLocalInertia(mass, localInertia);
                }

                //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
                btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape.get(), localInertia);
                btRigidBody* body = new btRigidBody(rbInfo);

                //add the body to the dynamics world
                m_world->addRigidBody(body);
            }

            {
                //create a dynamic rigidbody

                //btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
                auto colShape = std::make_unique<btSphereShape>(btScalar(1.));

                /// Create Dynamic Objects
                btTransform startTransform;
                startTransform.setIdentity();

                btScalar mass(1.f);

                //rigidbody is dynamic if and only if mass is non zero, otherwise static
                bool isDynamic = (mass != 0.f);

                btVector3 localInertia(0, 0, 0);
                if (isDynamic == true)
                    colShape->calculateLocalInertia(mass, localInertia);

                startTransform.setOrigin(btVector3(2, 10, 0));

                //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
                btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
                btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape.get(), localInertia);
                btRigidBody* body = new btRigidBody(rbInfo);

                m_collisionShapes.push_back(std::move(colShape));

                m_world->addRigidBody(body);
            }

            /// Do some simulation

            ///-----stepsimulation_start-----
            for (auto i = 0; i < 150; i++)
            {

                // //print positions of all objects
                // for (int j = m_world->getNumCollisionObjects() - 1; j >= 0; j--)
                // {
                //     btCollisionObject* obj = m_world->getCollisionObjectArray()[j];
                //     btRigidBody* body = btRigidBody::upcast(obj);
                //     btTransform trans;
                //     if (body && body->getMotionState())
                //     {
                //         body->getMotionState()->getWorldTransform(trans);
                //     }
                //     else
                //     {
                //         trans = obj->getWorldTransform();
                //     }
                //     printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
                // }
            }

            ///-----stepsimulation_end-----

        }

        m_bulletDebugugger->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
        m_world->setDebugDrawer(m_bulletDebugugger.get());

        return true;
    }

    bool PhysicsSystem::connect(SystemConnector & connector)
    {
        m_imguiSystem = connector.findSystem<ImguiSystem>();
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
            ImGui::End();
        }

        if (m_renderDebug == true)
        {
            m_world->debugDrawWorld();
            m_bulletDebugugger->doDrawing();
            m_bulletDebugugger->render();
            m_bulletDebugugger->clearBuffer();
            m_bulletDebugugger->cleanDrawing();
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
