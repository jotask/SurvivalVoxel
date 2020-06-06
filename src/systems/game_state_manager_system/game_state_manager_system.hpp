#pragma once

#include "systems/system_interface.hpp"
#include "systems/game_state_manager_system/state.hpp"

namespace aiko
{

    class ImguiSystem;

    class GameStateManager : public System
    {
    public:

        GameStateManager();
        virtual ~GameStateManager() override;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;

        virtual void preUpdate() override;
        virtual void update() override;
        virtual void postUpdate() override;

        virtual void preRender() override;
        virtual void render() override;
        virtual void postRender() override;

        template<class T, class ...Args>
        void pushState(Args...)
        {
            m_states.emplace_back(std::make_unique<T>(Args...));
            while (getCurrentState()->onEnter() == false);
        }

        State* getCurrentState();

        void popState();

    private:

        bool m_renderImgui;

        ImguiSystem* m_imguiSystem;

        std::vector<AikoUPtr<State>> m_states;

    };

}
