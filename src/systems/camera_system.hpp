#pragma once

#include "systems/system_interface.hpp"

#include "systems/event_system/event.hpp"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace aiko
{

    class DisplaySystem;
    class ImguiSystem;
    class ShaderSystem;

    class CameraSystem : public System
    {
    public:

        CameraSystem();
        virtual ~CameraSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

    public:
        void setViewport(int x, int y, int width, int height);
        glm::vec4 getViewport() const;
        void setProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);
        void applyViewMatrix();
        void setPosition(const glm::vec3& position);
        glm::vec3 getPosition() const;
        void translate(const glm::vec3& delta, bool local = true);
        void setRotation(const glm::quat& rotation);
        glm::quat getRotation() const;
        void setEularAngle(const glm::vec3& eularAngles);
        glm::vec3 getEularAngles() const;
        void rotate(const glm::quat& rotation);
        glm::mat4 getProjectionMatrix() const;
        glm::mat4 getViewMatrix();

        glm::vec3 getForward() const;
        glm::vec3 getRight() const;
        glm::vec3 getUp() const;

    private:

        void onWindowResize(Event&);

        void updateViewMatrix();

        glm::vec4 m_viewport;
        glm::vec3 m_position;
        glm::vec3 m_targetPosition;
        glm::quat m_rotation;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_projectionMatrix;

        bool isViewDirty;

        DisplaySystem* m_displaySystem;
        ImguiSystem* m_imguiSystem;
        ShaderSystem* m_shaderSystem;

        float m_radius;
        float m_speed;
        bool  m_autoRotationEnblad;

        bool m_renderImgui;

    };

}
