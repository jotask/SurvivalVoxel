#pragma once

#include "systems/system_interface.hpp"

#include <map>
#include <string>

namespace aiko
{

    class DisplaySystem;

    class ImguiSystem : public System
    {
    public:

        ImguiSystem();
        virtual ~ImguiSystem() override = default;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void render() override;

        virtual void beginFrame() override;
        virtual void endFrame() override;

        void registerSystem(std::string, bool&);

    private:

        bool m_showDemoWindow;
        bool m_showConsole;

        DisplaySystem* m_displaySystem;

        std::map<std::string, bool&> m_systemsEnabled;

    };

}
