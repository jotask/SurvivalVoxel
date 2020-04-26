#pragma once

#include "system/system_interface.hpp"

struct GLFWwindow;

namespace engine
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

    private:

        GLFWwindow* m_window;

    };

}
