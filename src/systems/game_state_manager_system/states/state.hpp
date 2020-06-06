#pragma once

#include "systems/game_state_manager_system/game_state_manager_system.hpp"

namespace aiko
{

    class State
    {
    public:

        State() = default;
        virtual ~State() = default;

        virtual bool onEnter() = 0;
        virtual bool onUpdate(GameStateManagerSystem* gsm) = 0;
        virtual bool onExit() = 0;

    };

}
