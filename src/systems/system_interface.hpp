#pragma once

#include "systems/system_connector.hpp"

namespace engine
{
    class System
    {
        public:
            System() = default;
            virtual ~System() = default;

            virtual bool connect(SystemConnector&) { return true; };

            virtual bool init() { return true; };

            virtual void preUpdate() { };
            virtual void update() { };
            virtual void postUpdate() { };

            virtual void preRender() { };
            virtual void render() { };
            virtual void postRender() { };

            virtual void beginFrame() { };
            virtual void endFrame() { };

    };
}
