#pragma once

namespace aiko
{

    class State
    {

    public:

        State() = default;
        ~State() = default;

        bool onEnter();
        bool onUpdate();
        bool onExit();

    };

}
