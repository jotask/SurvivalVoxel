#pragma once

#include "system/system_interface.hpp"


namespace engine
{

    class EntityComponentSystem : public System
    {
    public:

        EntityComponentSystem();
        virtual ~EntityComponentSystem() override = default;

        virtual bool init() override;
        virtual bool connect(SystemConnector&) override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

    private:

    };

}
