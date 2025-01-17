#include "systems/camera_system.hpp"

#include "systems/display_system.hpp"
#include "systems/imgui_system/imgui_system.hpp"
#include "systems/event_system/event_system.hpp"
#include "systems/shader_system/shader_system.hpp"
#include "systems/event_system/engine_events.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace aiko
{

    CameraSystem::CameraSystem()
        : m_viewport(0.f)
        , m_position(0.f)
        , m_targetPosition(0.f, 0.f, 0.f)
        , m_rotation()
        , m_viewMatrix(1.f)
        , m_projectionMatrix(1.f)
        , isViewDirty(false)
        , m_displaySystem(nullptr)
        , m_imguiSystem(nullptr)
        , m_shaderSystem(nullptr)
        , m_radius (50.0f)
        , m_speed(0.25f)
        , m_autoRotationEnblad(true)
        , m_renderImgui(false)
    {

    }

    bool CameraSystem::connect(SystemConnector & connector)
    {
        m_displaySystem = connector.findSystem<DisplaySystem>();
        m_imguiSystem = connector.findSystem<ImguiSystem>();
        m_shaderSystem = connector.findSystem<ShaderSystem>();
        return true;
    }

    bool CameraSystem::init()
    {

        EventSystem::it().bind<WindowResizeEvent>(this, &CameraSystem::onWindowResize);

        m_imguiSystem->registerSystem("CameraSystem", m_renderImgui);

        const auto windowSize = m_displaySystem->getWindowSize();

        setPosition({0.f, 25.f, 0.f});
        setProjectionMatrix(45.f, windowSize.x / windowSize.y, 0.1f, 1000.f);

        setViewport(0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));
        return true;
    }

    void CameraSystem::preUpdate()
    {

    }

    void CameraSystem::update()
    {

    }

    void CameraSystem::postUpdate()
    {

    }

    void CameraSystem::preRender()
    {

    }

    void CameraSystem::render()
    {
        if (m_renderImgui == true)
        {
            ImGui::Begin("Camera settings", &m_renderImgui);
            ImGui::Checkbox("Rotation enabled", &m_autoRotationEnblad);
            if (m_autoRotationEnblad == true)
            {
                ImGui::SliderFloat("Radius", &m_radius, 0.f, 100.f);
                ImGui::SliderFloat("Speed", &m_speed, 0.f, 1.f);
            }
            if (ImGui::CollapsingHeader("Position") == true)
            {
                ImGui::SliderFloat("PX", &m_position.x, -50, 100);
                ImGui::SliderFloat("PY", &m_position.y, -50, 100);
                ImGui::SliderFloat("PZ", &m_position.z, -50, 100);
            }
            if (ImGui::CollapsingHeader("Target") == true)
            {
                ImGui::SliderFloat("TX", &m_targetPosition.x, -50, 100);
                ImGui::SliderFloat("TY", &m_targetPosition.y, -50, 100);
                ImGui::SliderFloat("TZ", &m_targetPosition.z, -50, 100);
            }
            ImGui::End();
            isViewDirty = true;
            updateViewMatrix();

        }
        for (auto& shaderPair : m_shaderSystem->getShaders())
        {
            auto& shader = shaderPair.second;
            shader->use();
            shader->setVec3("viewPos", m_position);
            shader->setMat4("projection", getProjectionMatrix());
            shader->setMat4("view", getViewMatrix());
        }
    }

    void CameraSystem::postRender()
    {

    }

    void CameraSystem::setViewport(int x, int y, int width, int height)
    {
        m_viewport = glm::vec4(x, y, width, height);
        glViewport(x, y, width, height);
    }

    glm::vec4 CameraSystem::getViewport() const
    {
        return m_viewport;
    }

    void CameraSystem::setProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
    {
        m_projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

    void CameraSystem::applyViewMatrix()
    {
        updateViewMatrix();
    }

    void CameraSystem::setPosition(const glm::vec3 & position)
    {
        m_position = position;
        isViewDirty = true;
    }

    glm::vec3 CameraSystem::getPosition() const
    {
        return m_position;
    }

    void CameraSystem::translate(const glm::vec3 & delta, bool local)
    {
        if (local == true)
        {
            m_position += m_rotation * delta;
        }
        else
        {
            m_position += delta;
        }
        isViewDirty = true;
    }

    void CameraSystem::setRotation(const glm::quat & rotation)
    {
        m_rotation = rotation;
        isViewDirty = true;
    }

    glm::quat CameraSystem::getRotation() const
    {
        return m_rotation;
    }

    void CameraSystem::setEularAngle(const glm::vec3 & eularAngles)
    {
        m_rotation = glm::quat(glm::radians(eularAngles));
    }

    glm::vec3 CameraSystem::getEularAngles() const
    {
        return glm::degrees(glm::eulerAngles(m_rotation));
    }

    void CameraSystem::rotate(const glm::quat & rotateBy)
    {
        m_rotation *= rotateBy;
        isViewDirty = true;
    }

    glm::mat4 CameraSystem::getProjectionMatrix() const
    {
        return m_projectionMatrix;
    }

    glm::mat4 CameraSystem::getViewMatrix()
    {
        updateViewMatrix();
        return m_viewMatrix;
    }

    glm::vec3 CameraSystem::getForward() const
    {
        return { 0.0f, 0.0f, -1.0f };
    }

    glm::vec3 CameraSystem::getRight() const
    {
        return { 1.0f, 0.0f, 0.0f };
    }

    glm::vec3 CameraSystem::getUp() const
    {
        return { 0.0f, 1.0f, 0.0f };
    }

    void CameraSystem::onWindowResize(Event & evnt)
    {
        const auto& msg = static_cast<const WindowResizeEvent&>(evnt);
        setViewport(0, 0, static_cast<int>(msg.width), static_cast<int>(msg.height));
        setProjectionMatrix(45.f, msg.width / static_cast<float>(msg.height), 0.1f, 1000.f);
    }

    void CameraSystem::updateViewMatrix()
    {
        if (isViewDirty == true)
        {
            if (false)
            {
                glm::mat4 translate = glm::translate(-m_position);
                glm::mat4 rotate = glm::transpose(glm::toMat4(m_rotation));
                m_viewMatrix = rotate * translate;
                m_viewMatrix = glm::lookAt(m_position, {0.f, 0.f, 0.f}, getUp());
                isViewDirty = false;
            }
            else
            {
                m_viewMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first

                float camX = m_position.x;
                float camY = m_position.y;
                float camZ = m_position.z;

                if (m_autoRotationEnblad == true)
                {
                    camX += static_cast<float>(sin(glfwGetTime() * m_speed) * m_radius);
                    camZ += static_cast<float>(cos(glfwGetTime() * m_speed) * m_radius);
                }

                m_viewMatrix = glm::lookAt({camX, camY, camZ}, m_targetPosition, getUp());
            }

        }
    }

}
