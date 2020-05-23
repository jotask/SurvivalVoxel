#pragma once

#include "systems/entity_component_system/components/mesh_component.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "systems/chunk_system/vertex_info.hpp"
#include "systems/chunk_system/chunk.hpp"
#include "systems/shader_system/shader.hpp"
#include "utils/shared.hpp"
#include "engine.hpp"
#include "systems/entity_component_system/components/mesh_component.hpp"
#include "systems/physics_system/rigid_body_converter.hpp"
#include "systems/physics_system/rigid_body_data.hpp"
#include "utils/transform.hpp"

#include <btBulletDynamicsCommon.h>

#include <memory>
#include <random>


namespace engine
{
    namespace factory
    {
        namespace physics
        {

            static AikoUPtr<btTriangleMesh> createStaticCollisionShapeFromMeshData(Transform transform, Mesh::MeshData& mesh)
            {

                auto shape = std::make_unique<btTriangleMesh>();

                for (int i = 0 ; i < mesh.indices.size() ; i += 3)
                {
                    auto v1 = mesh.vertices[mesh.indices[i + 0]].m_position;
                    auto v2 = mesh.vertices[mesh.indices[i + 1]].m_position;
                    auto v3 = mesh.vertices[mesh.indices[i + 2]].m_position;
                    shape->addTriangle({ v1.x, v1.y, v1.z }, { v2.x, v2.y, v2.z }, { v3.x, v3.y, v3.z });
                }

                return std::move(shape);
            }

            static AikoUPtr<btConvexHullShape> createConvexHullCollisionShapeFromMeshData(Transform transform, Mesh::MeshData& mesh)
            {

                auto shape = std::make_unique<btConvexHullShape>();

                for (auto& v : mesh.vertices)
                {
                    shape->addPoint(engine::physics::converter::glmToBullet(v.getVertexPosition()));
                }

                return std::move(shape);
            }

        }
    }
}

