#pragma once

#include "systems/imgui_system/commands_functions.hpp"

#include <map>
#include <string>
#include <functional>

namespace aiko
{
    namespace commands
    {

        CommandMap s_commands = {
            {"HELP", &command_Help},
            {"CLEAR", &command_Clear},
        };

    }
}
