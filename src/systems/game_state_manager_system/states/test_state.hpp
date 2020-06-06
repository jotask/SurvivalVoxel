#pragma once

#include "systems/game_state_manager_system/states/state.hpp"

namespace aiko
{

    class TestState : public State
    {
    public:

        TestState() = default;
        virtual ~TestState() = default;

        virtual bool onEnter();
        virtual bool onUpdate(GameStateManagerSystem* gsm);
        virtual bool onExit();

    };

}
