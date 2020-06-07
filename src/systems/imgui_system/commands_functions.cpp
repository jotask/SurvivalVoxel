#include "commands_functions.hpp"

#include "systems/imgui_system/imgui_console.hpp"
#include "systems/imgui_system/commands.hpp"

namespace aiko
{

    namespace commands
    {

        void command_Help(AikoConsole* console)
        {
            console->addLog("Commands:");
            for (auto& command : s_commands)
            {
                console->addLog("- %s", command.first.c_str());
            }
        }

        void command_Clear(AikoConsole* console)
        {
            console->clearLog();
        }

        void command_History(AikoConsole* console)
        {
            // int first = m_history.size() - 10;
            // for (int i = first > 0 ? first : 0; i < m_history.size(); i++)
            //     addLog("%3d: %s\n", i, m_history[i]);
        }

    }
}
