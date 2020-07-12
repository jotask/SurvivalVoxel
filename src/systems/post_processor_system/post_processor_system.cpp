#include "systems/post_processor_system/post_processor_system.hpp"

#include "systems/shader_system/shader.hpp"
#include "systems/render_system/render_system.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "systems/event_system/engine_events.hpp"
#include "systems/event_system/event_system.hpp"
#include "systems/display_system.hpp"

#include "systems/post_processor_system/effects/blur_effect.hpp"
#include "systems/post_processor_system/effects/shake_effect.hpp"
#include "systems/post_processor_system/effects/edge_effect.hpp"
#include "systems/post_processor_system/effects/invert_colors_effect.hpp"
#include "systems/post_processor_system/effects/chaos_effect.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <imgui.h>

#include <array>

namespace aiko
{
    PostProcessorSystem::PostProcessorSystem()
        : m_renderSystem(nullptr)
        , m_displaySystem(nullptr)
        , m_shaderSystem(nullptr)
        , m_shader(nullptr)
        , m_texture()
        , m_vao(-1)
        , m_fbo(-1)
        , m_rbo(-1)
        , m_width(0)
        , m_height(0)
        , m_renderEffects(true)
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

        // Generate frambuffer
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        // create a color attachment texture
        m_texture.init();
        m_texture.generate(m_width, m_height, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.getId(), 0);

        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
        glGenRenderbuffers(1, &m_rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo); // now actually attach it

        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            spdlog::error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
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

            m_effects.emplace_back(std::make_unique<postprocessing::BlurFx>());
            m_effects.emplace_back(std::make_unique<postprocessing::ShakeFx>());
            m_effects.emplace_back(std::make_unique<postprocessing::EdgeFx>());
            m_effects.emplace_back(std::make_unique<postprocessing::InvertColorsFx>());
            m_effects.emplace_back(std::make_unique<postprocessing::ChaosFx>());

            {
                constexpr const float offset = 1.0f / 300.0f;
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
            }

            for (auto& fx : m_effects)
            {
                fx->init(m_shader);
            }

            m_shader->unuse();
        }

        return true;
    }

    void PostProcessorSystem::preRender()
    {

    }

    void PostProcessorSystem::render()
    {
        ImGui::Begin("PostProcessorSystem");
        ImGui::Checkbox("SystemEnabled", &m_renderEffects);
        for (auto& fx : m_effects)
        {
            ImGui::Checkbox(fx->getName().c_str(), &fx->isEnabled());
            if (fx->isEnabled() == true)
            {
                fx->updateSettings();
            }
        }
        ImGui::End();
    }

    void PostProcessorSystem::postRender()
    {

    }

    void PostProcessorSystem::beginFrame()
    {
        if (m_renderEffects)
        {
             // bind to framebuffer and draw scene as we normally would to color texture 
            glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
            glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

            // make sure we clear the framebuffer's content
            auto color = m_renderSystem->getBackgroundColor();
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
            // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // disable depth test so screen-space quad isn't discarded due to depth test.
            glDisable(GL_DEPTH_TEST);

            // clear all relevant buffers
            const auto color = m_renderSystem->getBackgroundColor();
            glClearColor(color.r, color.g, color.b, color.a);
            glClear(GL_COLOR_BUFFER_BIT);

            // set uniforms/options
            m_shader->use();
            m_shader->setFloat("time", static_cast<float>(glfwGetTime()));
            for (auto& fx : m_effects)
            {
                fx->use(m_shader);
            }

            // render textured quad
            glBindVertexArray(m_vao);
            m_texture.bind();
            glDrawArrays(GL_TRIANGLES, 0, 6);

            m_shader->unuse();
        }
    }

    void PostProcessorSystem::onWindowResize(Event & evnt)
    {
        const auto& msg = static_cast<const WindowResizeEvent&>(evnt);
        m_width = msg.width;
        m_height = msg.height;
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        m_texture.bind();
        m_texture.generate(m_width, m_height, nullptr);
        glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

}
