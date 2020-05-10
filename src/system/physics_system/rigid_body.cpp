#include "rigid_body.hpp"

#include "engine.hpp"
#include "system/physics_system/physics_system.hpp"
#include "system/entity_component_system/entity.hpp"
#include "system/entity_component_system/components/mesh_component.hpp"
#include "system/physics_system/rigid_body_factory.hpp"

#include <btBulletDynamicsCommon.h>

namespace engine
{

    RigidBody::RigidBody(Entity* entity, physics::RigidBodyData data)
        : Component(entity)
        , m_data(data)
        , m_triangleMesh(nullptr)
    {

        // Create a dynamic rigidbody


        btCollisionShape* collisionShape = nullptr;;

        if (entity->hasComponent<Mesh>() == true)
        {
            auto& mesh = entity->getComponent<Mesh>();
            m_triangleMesh = std::move(factory::physics::createCollisionShapeFromMeshData(getEntity()->getTransform(), mesh.getMeshData()));
            collisionShape = new btBvhTriangleMeshShape(m_triangleMesh.get(), true);
        }
        else
        {
            collisionShape = new btSphereShape(btScalar(1.));
        }

        // Create Dynamic Objects
        auto startTransform = btTransform();
        startTransform.setIdentity();
        auto pos = getEntity()->getTransform().position;
        startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

        const auto isDynamic = (m_data.mass != 0.f);

        auto localInertia = btVector3(0, 0, 0);
        if (isDynamic == true)
        {
            collisionShape->calculateLocalInertia(data.mass, localInertia);
        }

        auto* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(m_data.mass, myMotionState, collisionShape, localInertia);
        auto* body = new btRigidBody(rbInfo);

        body->setRestitution(m_data.m_restitution);

        body->setUserPointer(this);

        auto* physicsSystem = engine::Engine::getInstance().getSystem<PhysicsSystem>();
        physicsSystem->addRigidBodyToWorld(body);

    }

}