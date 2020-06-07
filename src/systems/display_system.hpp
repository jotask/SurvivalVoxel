#pragma once

#include "systems/system_interface.hpp"

#include <glm/glm.hpp>

struct GLFWwindow;

namespace aiko
{

    class DisplaySystem : public System
    {
    public:

        DisplaySystem();
        virtual ~DisplaySystem() override;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        GLFWwindow* getWindow() const;

        glm::vec2 getWindowSize() const;

        // Not happy but maybe change this for an event?
        bool shouldWindowClose() const;

        void swapBuffers() const;

    private:

        GLFWwindow* m_window;

        bool        m_lockFps;

    };

}
