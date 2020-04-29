#include "system/chunk_system.hpp"

#include "system/render_system.hpp"
#include "system/camera_system.hpp"
#include "system/chunk.hpp"

#include <imgui.h>

#include <algorithm>

namespace engine
{

    ChunkSystem::ChunkSystem()
        : m_renderSystem(nullptr)
        , m_cameraSystem(nullptr)
        , m_lightPos(0.f)
        , m_lightCol(1.f, 0.f, 0.25f)
    {

    }

    ChunkSystem::~ChunkSystem()
    {

    }

    bool ChunkSystem::init()
    {
        constexpr auto size = 2;
        for (auto z = -size; z < size; z++)
        {
            for (auto x = -size; x < size; x++)
            {
                auto chunk = Chunk(this, x, z);
                chunk.generate();
                m_chunks.push_back(std::move(chunk));
            }
        }
        return true;
    }

    bool ChunkSystem::connect(SystemConnector & connector)
    {
        m_renderSystem = connector.findSystem<RenderSystem>();
        m_cameraSystem = connector.findSystem<CameraSystem>();
        return true;
    }

    void ChunkSystem::preUpdate()
    {

    }

    void ChunkSystem::update()
    {

    }

    void ChunkSystem::postUpdate()
    {

    }

    void ChunkSystem::preRender()
    {

    }

    void ChunkSystem::render()
    {
        if (ImGui::Begin("Light") == true)
        {
            ImGui::SliderFloat("XPos", &m_lightPos.x, -100, 100);
            ImGui::SliderFloat("YPos", &m_lightPos.y, -100, 100);
            ImGui::SliderFloat("ZPos", &m_lightPos.z, -100, 100);
            ImGui::ColorEdit3("RColor", &m_lightCol.x);
            ImGui::End();
        }
        auto program = m_chunks[0].getMesh()->getProgram();
        glUniform3f(glGetUniformLocation(program, "u_lightPos"), m_lightPos.x, m_lightPos.y, m_lightPos.z);
        glUniform3f(glGetUniformLocation(program, "u_lightCol"), m_lightCol.x, m_lightCol.y, m_lightCol.z);
        for (auto& chunk : m_chunks)
        {
            chunk.renderMesh();
        }
    }

    void ChunkSystem::postRender()
    {

    }

}
