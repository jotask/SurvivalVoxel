#pragma once

#include "systems/system_interface.hpp"


namespace aiko
{

    class DisplaySystem;

    class InputSystem : public System
    {
    public:

        InputSystem();
        virtual ~InputSystem() override = default;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

    private:

        DisplaySystem* m_displaySystem;

    };

}
