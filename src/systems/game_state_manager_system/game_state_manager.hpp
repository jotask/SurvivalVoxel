#pragma once

#include "systems/game_state_manager_system/states/state.hpp"

#include <optional>

namespace aiko
{

    class GameStateManager
    {
    public:

        GameStateManager() = default;
        ~GameStateManager() = default;


        template<class T>
        void changeState()
        {
            static_assert(std::is_base_of<State, T>::value, "State is not base from the abstract state class!");
            m_nextState = std::make_unique<T>(this);
        }

        State* getCurrentState()
        {
            if (m_states.empty() == false)
            {
                return nullptr;
            }
            else
            {
                return m_states.back().get();
            }
        }

    private:

        std::vector<AikoUPtr<State>> m_states;

        std::optional<AikoUPtr<State>> m_nextState;

    };

}
