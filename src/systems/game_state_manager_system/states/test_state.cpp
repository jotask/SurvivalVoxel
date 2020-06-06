#include "test_state.hpp"

namespace aiko
{

    bool TestState::onEnter()
    {
        return true;
    }

    bool TestState::onUpdate(GameStateManagerSystem* gsm)
    {
        return true;
    }

    bool TestState::onExit()
    {
        return true;
    }

}