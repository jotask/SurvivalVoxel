#include "rigid_body.hpp"

#include "engine.hpp"
#include "systems/physics_system/physics_system.hpp"
#include "systems/entity_component_system/entity.hpp"
#include "systems/entity_component_system/components/mesh_component.hpp"
#include "systems/physics_system/rigid_body_factory.hpp"

#include <btBulletDynamicsCommon.h>

namespace aiko
{

    RigidBody::RigidBody(Entity* entity, physics::RigidBodyData data)
        : Component(entity)
        , m_data(data)
        , m_triangleMeshStatic(nullptr)
        , m_collisionShape(nullptr)
    {

        const auto isDynamic = (m_data.mass != 0.f);

        if (entity->hasComponent<Mesho>() == true)
        {
            auto& mesh = entity->getComponent<Mesho>();
            if (isDynamic == false)
            {
                m_triangleMeshStatic = std::move(factory::physics::createStaticCollisionShapeFromMeshData(getEntity()->getTransform(), mesh.getMeshData()));
                m_collisionShape = std::make_unique<btBvhTriangleMeshShape>(m_triangleMeshStatic.get(), true);
            }
            else
            {
                m_collisionShape = std::move(factory::physics::createConvexHullCollisionShapeFromMeshData(getEntity()->getTransform(), mesh.getMeshData()));
            }
        }
        else
        {
            m_collisionShape = std::make_unique<btSphereShape>(btScalar(1.));
        }

        auto startTransform = btTransform();
        startTransform.setIdentity();
        startTransform.setOrigin(physics::converter::glmToBullet(getEntity()->getTransform().position));
        // TODO implement rotation

        auto localInertia = btVector3(0, 0, 0);
        if (isDynamic == true)
        {
            m_collisionShape->calculateLocalInertia(data.mass, localInertia);
        }

        auto* myMotionState = new btDefaultMotionState(startTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(m_data.mass, myMotionState, m_collisionShape.get(), localInertia);
        auto* body = new btRigidBody(rbInfo);

        body->setRestitution(m_data.m_restitution);

        body->setUserPointer(getEntity());

        auto* physicsSystem = aiko::Engine::getInstance().getSystem<PhysicsSystem>();
        physicsSystem->addRigidBodyToWorld(body);

    }

}