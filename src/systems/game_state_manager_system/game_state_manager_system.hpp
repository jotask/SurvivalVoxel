#pragma once

#include "systems/system_interface.hpp"

#include <optional>
#include <utility>

namespace aiko
{

    class ImguiSystem;
    class State;

    class GameStateManagerSystem : public System
    {
    public:

        GameStateManagerSystem();
        virtual ~GameStateManagerSystem() override;

        virtual bool connect(SystemConnector&) override;
        virtual bool init() override;
        virtual void update() override;
        virtual void postUpdate() override;
        virtual void render() override;

        template<class T>
        void changeState(bool popLastState = true)
        {
            static_assert(std::is_base_of<State, T>::value, "State is not base from the abstract state class!");
            m_nextState = std::make_pair(popLastState, std::make_unique<T>());
        }

        void popState();

    private:
        State* getCurrentState();

        bool m_renderImgui;

        ImguiSystem* m_imguiSystem;

        std::vector<AikoUPtr<State>> m_states;

        std::optional<std::pair<bool, AikoUPtr<State>>> m_nextState;

        bool m_popLastState;

    };

}
