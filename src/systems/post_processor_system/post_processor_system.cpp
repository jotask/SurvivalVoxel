#include "systems/post_processor_system/post_processor_system.hpp"

#include "systems/shader_system/shader.hpp"
#include "systems/render_system/render_system.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "systems/event_system/engine_events.hpp"
#include "systems/event_system/event_system.hpp"
#include "systems/display_system.hpp"

#include "GLFW/glfw3.h"

#include <spdlog/spdlog.h>
#include <imgui.h>

namespace aiko
{
    PostProcessorSystem::PostProcessorSystem()
        : m_renderSystem(nullptr)
        , m_displaySystem(nullptr)
        , m_shaderSystem(nullptr)
        , m_shader(nullptr)
        , m_msfbo(-1)
        , m_fbo(-1)
        , m_rbo(-1)
        , m_vao(-1)
        , m_width(0)
        , m_height(0)
        , m_renderEffects(true)
        , m_chaos(false)
        , m_confuse(false)
        , m_shake(false)
    {

    }

    bool PostProcessorSystem::connect(SystemConnector & connector)
    {
        m_renderSystem = connector.findSystem<RenderSystem>();
        m_displaySystem = connector.findSystem<DisplaySystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();
        return true;
    }

    bool PostProcessorSystem::init()
    {

        EventSystem::it().bind<WindowResizeEvent>(this, &PostProcessorSystem::onWindowResize);

        auto windowSize = m_displaySystem->getWindowSize();
        m_width = static_cast<unsigned int>(windowSize.x);
        m_height = static_cast<unsigned int>(windowSize.y);

        m_shader = &m_shaderSystem->getShader("postProcessing");

        // initialize renderbuffer/framebuffer object
        glGenFramebuffers(1, &m_msfbo);
        glGenFramebuffers(1, &m_fbo);
        glGenRenderbuffers(1, &m_rbo);

        // initialize renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
        glBindFramebuffer(GL_FRAMEBUFFER, m_msfbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, m_width, m_height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_rbo);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            spdlog::error("Postprocessor: Failed to initialize MSFBO");
            return false;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        m_texture.generate(m_width, m_height, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.getId(), 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_fbo);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_fbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            spdlog::error("Postprocessor: Failed to initialize FBO");
            return false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Init render stuff
        {
            constexpr float vertices[] = {
                // pos        // tex
                -1.0f, -1.0f, 0.0f, 0.0f,
                 1.0f,  1.0f, 1.0f, 1.0f,
                -1.0f,  1.0f, 0.0f, 1.0f,

                -1.0f, -1.0f, 0.0f, 0.0f,
                 1.0f, -1.0f, 1.0f, 0.0f,
                 1.0f,  1.0f, 1.0f, 1.0f
            };
            GLuint vbo;
            glGenVertexArrays(1, &m_vao);
            glGenBuffers(1, &vbo);

            glBindBuffer(GL_ARRAY_BUFFER, m_vao);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindVertexArray(m_vao);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

        }

        {
            m_shader->use();
            float offset = 1.0f / 300.0f;
            float offsets[9][2] = {
                { -offset,  offset  },  // top-left
                {  0.0f,    offset  },  // top-center
                {  offset,  offset  },  // top-right
                { -offset,  0.0f    },  // center-left
                {  0.0f,    0.0f    },  // center-center
                {  offset,  0.0f    },  // center - right
                { -offset, -offset  },  // bottom-left
                {  0.0f,   -offset  },  // bottom-center
                {  offset, -offset  }   // bottom-right    
            };
            glUniform2fv(glGetUniformLocation(m_shader->getProgramId(), "offsets"), 9, (float*)offsets);
            int edge_kernel[9] = {
                -1, -1, -1,
                -1,  8, -1,
                -1, -1, -1
            };
            glUniform1iv(glGetUniformLocation(m_shader->getProgramId(), "edge_kernel"), 9, edge_kernel);
            float blur_kernel[9] = {
                1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
                2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
                1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
            };
            glUniform1fv(glGetUniformLocation(m_shader->getProgramId(), "blur_kernel"), 9, blur_kernel);
            m_shader->unuse();
        }

        return true;
    }

    void PostProcessorSystem::preUpdate()
    {

    }

    void PostProcessorSystem::update()
    {

    }

    void PostProcessorSystem::postUpdate()
    {

    }

    void PostProcessorSystem::preRender()
    {
        ImGui::Begin("PostProcessorSystem");
        ImGui::Checkbox("SystemEnabled", &m_renderEffects);
        ImGui::Checkbox("Chaos", &m_chaos);
        ImGui::Checkbox("Shake", &m_shake);
        ImGui::Checkbox("Confuse", &m_confuse);
        ImGui::End();
    }

    void PostProcessorSystem::render()
    {
        
    }

    void PostProcessorSystem::postRender()
    {

    }

    void PostProcessorSystem::beginFrame()
    {
        if (m_renderEffects)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, m_msfbo);
            const auto color = m_renderSystem->getBackgroundColor();
            glClearColor(color.r, color.g, color.b, color.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }

    void PostProcessorSystem::endFrame()
    {
        if (m_renderEffects)
        {
            glBindFramebuffer(GL_READ_FRAMEBUFFER, m_msfbo);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
            glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // set uniforms/options
            m_shader->use();

            m_shader->setBool("confuse", m_confuse);
            m_shader->setBool("chaos", m_chaos);
            m_shader->setBool("shake", m_shake);
            m_shader->setFloat("time", static_cast<float>(glfwGetTime()));

            // render textured quad
            glActiveTexture(GL_TEXTURE0);
            m_texture.bind();
            glBindVertexArray(m_vao);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);

            m_shader->unuse();
        }
    }

    void PostProcessorSystem::onWindowResize(Event & evnt)
    {
        const auto& msg = static_cast<const WindowResizeEvent&>(evnt);
        m_width = msg.width;
        m_height = msg.height;

        glBindFramebuffer(GL_FRAMEBUFFER, m_msfbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, m_width, m_height);
        m_texture.generate(m_width, m_height, nullptr);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        m_texture.generate(m_width, m_height, nullptr);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}
