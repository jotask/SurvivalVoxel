#pragma once

#include <map>
#include <functional>

namespace aiko
{

    class AikoConsole;

    namespace commands
    {

        using CommandCallbackFntParameters = void(AikoConsole*);
        using CommandCallbackFnt = std::function<CommandCallbackFntParameters>;
        using CommandMap = std::map<std::string, CommandCallbackFnt>;

    }
}
