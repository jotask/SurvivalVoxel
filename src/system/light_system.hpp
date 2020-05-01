#pragma once

#include "system/system_interface.hpp"

namespace engine
{

    class LightSystem : public System
    {
    public:

        LightSystem();
        virtual ~LightSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

    private:

    };

}
